#include <sanguis/duration.hpp>
#include <sanguis/main_object.hpp>
#include <sanguis/client/create_systems.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/client/object.hpp>
#include <sanguis/client/systems.hpp>
#include <sanguis/client/config/settings/file.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/states/menu.hpp>
#include <sanguis/server/object.hpp>
#include <sge/config/media_path.hpp>
#include <sge/font/object.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/system.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/window/system.hpp>
#include <alda/net/port.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/fatal.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::object::object(
	boost::program_options::variables_map const &_variables_map
)
:
	sanguis::main_object(),
	settings_(
		client::config::settings::file()
	),
	saver_(
		settings_
	),
	io_service_(),
	sys_(
		sanguis::client::create_systems(
			_variables_map
		)
	),
	font_object_(
		sys_->font_system().create_font(
			sge::font::parameters()
		)
	),
	console_(
		FCPPT_TEXT('/')
	),
	console_gfx_(
		console_,
		sys_->renderer_ffp(),
		*font_object_,
		sys_->image_system(),
		sys_->keyboard_collector(),
		sys_->viewport_manager(),
		_variables_map[
			"history-size"
		].as<
			sge::console::output_line_limit
		>()
	),
	resources_(
		sys_->image_system(),
		sys_->renderer_core()
	),
	cursor_(
		sys_->cursor_demuxer()
	),
	gui_(
		sys_->renderer_ffp(),
		sys_->image_system(),
		sys_->charconv_system(),
		sys_->viewport_manager(),
		sys_->keyboard_collector(),
		cursor_
	),
	machine_(
		settings_,
		gui_,
		std::tr1::bind(
			&sanguis::client::object::create_server,
			this,
			std::tr1::placeholders::_1
		),
		resources_,
		sys_->window_system(),
		*font_object_,
		console_gfx_.get(),
		sys_->keyboard_collector(),
		cursor_,
		sys_->renderer_ffp(),
		sys_->charconv_system(),
		sys_->image_system(),
		io_service_,
		sys_->viewport_manager()
	),
	frame_timer_(
		sanguis::timer::parameters(
			boost::chrono::seconds(
				1
			)
		)
	),
	server_(),
	scoped_machine_(
		machine_
	)
{
}

sanguis::client::object::~object()
{
}

awl::main::exit_code const
sanguis::client::object::run()
{
	this->register_handler();

	io_service_.run();

	awl::main::exit_code const server_ret(
		this->quit_server()
	);

	return
		server_ret
		==
		awl::main::exit_failure()
		?
			awl::main::exit_failure()
		:
			sys_->window_system().exit_code();
}

void
sanguis::client::object::register_handler()
{
	io_service_.post(
		std::tr1::bind(
			&sanguis::client::object::loop_handler,
			this
		)
	);
}

void
sanguis::client::object::loop_handler()
{
	if(
		server_
		&& !server_->running()
	)
		sys_->window_system().quit(
			awl::main::exit_failure()
		);

	try
	{
		if(
			!machine_.process(
				sge::timer::elapsed_and_reset<
					sanguis::duration
				>(
					frame_timer_
				)
			)
		)
		{
			io_service_.stop();

			return;
		}

		machine_.draw();
	}
	catch(
		fcppt::exception const &_exception
	)
	{
		FCPPT_LOG_FATAL(
			sanguis::client::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Client error: ")
				<< _exception.string()
		);

		sys_->window_system().quit(
			awl::main::exit_failure()
		);

		this->quit_server();
	}

	this->register_handler();
}

void
sanguis::client::object::create_server(
	alda::net::port const _port
)
{
	if(
		server_
	)
	{
		this->quit_server();

		server_.reset();
	}

	server_.take(
		fcppt::make_unique_ptr<
			server::object
		>(
			_port,
			fcppt::cref(
				resources_
			),
			fcppt::ref(
				sys_->charconv_system()
			)
		)
	);
}

awl::main::exit_code const
sanguis::client::object::quit_server()
{
	if(
		server_
	)
		server_->quit();

	return
		server_
		?
			server_->run()
		:
			awl::main::exit_success()
		;
}
