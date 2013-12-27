#include <sanguis/duration.hpp>
#include <sanguis/io_service.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/load/context_fwd.hpp>
#include <sanguis/net/deserialize.hpp>
#include <sanguis/net/send_buffer_size.hpp>
#include <sanguis/net/serialize_to_circular_buffer.hpp>
#include <sanguis/net/receive_buffer_size.hpp>
#include <sge/console/gfx.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/systems/instance.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/system.hpp>
#include <awl/main/exit_success.hpp>
#include <alda/net/host.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/system/error_code.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::machine::machine(
	sanguis::client::config::settings::object &_settings,
	sanguis::client::server_callback const &_server_callback,
	sanguis::load::context const &_resources,
	sge::window::system &_window_system,
	sge::font::object &_font_object,
	sge::console::gfx &_console_gfx,
	sge::input::keyboard::device &_keyboard,
	sge::input::cursor::object &_cursor,
	sge::renderer::device::ffp &_renderer,
	sge::image2d::system &_image_loader,
	sanguis::io_service &_io_service,
	sge::viewport::manager &_viewport_manager
)
:
	settings_(
		_settings
	),
	resources_(
		_resources
	),
	keyboard_(
		_keyboard
	),
	renderer_(
		_renderer
	),
	image_loader_(
		_image_loader
	),
	viewport_manager_(
		_viewport_manager
	),
	net_(
		alda::net::parameters(
			_io_service.impl(),
			sanguis::net::send_buffer_size(),
			sanguis::net::receive_buffer_size()
		)
	),
	s_conn_(
		net_.register_connect(
			std::bind(
				&machine::connect_callback,
				this
			)
		)
	),
	s_disconn_(
		net_.register_error(
			std::bind(
				&machine::error_callback,
				this,
				std::placeholders::_1,
				std::placeholders::_2
			)
		)
	),
	s_data_(
		net_.register_data(
			std::bind(
				&machine::data_callback,
				this,
				std::placeholders::_1
			)
		)
	),
	window_system_(
		_window_system
	),
	font_object_(
		_font_object
	),
	console_gfx_(
		_console_gfx
	),
	server_callback_(
		_server_callback
	),
	cursor_(
		_cursor
	)
{
}

sanguis::client::machine::~machine()
{
}

void
sanguis::client::machine::quickstart(
	alda::net::port const _port
)
{
	FCPPT_LOG_DEBUG(
		sanguis::client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("machine::quickstart()")
	);

	server_callback_(
		_port
	);

	this->connect(
		alda::net::host(
			"localhost"
		),
		_port
	);
}

void
sanguis::client::machine::connect(
	alda::net::host const &_host,
	alda::net::port const _port
)
{
	net_.connect(
		_host,
		_port
	);
}

void
sanguis::client::machine::disconnect()
{
	net_.disconnect();
}

void
sanguis::client::machine::send(
	sanguis::messages::base const &_message
)
{
	if(
		!sanguis::net::serialize_to_circular_buffer(
			_message,
			net_.send_buffer()
		)
	)
	{
		FCPPT_LOG_ERROR(
			sanguis::client::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Not enough space left in the send_buffer")
		);
		// TODO:!
	}

	net_.queue_send();
}

bool
sanguis::client::machine::process(
	sanguis::duration const &_time
)
{
	this->process_event(
		events::tick(
			_time
		)
	);

	return
		window_system_.poll();
}

void
sanguis::client::machine::draw()
{
	sge::renderer::context::scoped_ffp const block(
		renderer_,
		renderer_.onscreen_target()
	);

	this->process_event(
		sanguis::client::events::render(
			block.get()
		)
	);
}

void
sanguis::client::machine::quit()
{
	FCPPT_LOG_DEBUG(
		client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Exiting the client!")
	);

	window_system_.quit(
		awl::main::exit_success()
	);
}

sanguis::client::config::settings::object &
sanguis::client::machine::settings()
{
	return settings_;
}

sge::renderer::device::ffp &
sanguis::client::machine::renderer() const
{
	return renderer_;
}

sge::image2d::system &
sanguis::client::machine::image_loader() const
{
	return image_loader_;
}

sge::input::keyboard::device &
sanguis::client::machine::keyboard() const
{
	return keyboard_;
}

sge::font::object &
sanguis::client::machine::font_object() const
{
	return font_object_;
}

sge::console::gfx &
sanguis::client::machine::console_gfx()
{
	return console_gfx_;
}

sanguis::load::context const &
sanguis::client::machine::resources() const
{
	return resources_;
}

sge::input::cursor::object &
sanguis::client::machine::cursor()
{
	return cursor_;
}

sge::input::cursor::object const &
sanguis::client::machine::cursor() const
{
	return cursor_;
}

sge::viewport::manager &
sanguis::client::machine::viewport_manager() const
{
	return viewport_manager_;
}

void
sanguis::client::machine::connect_callback()
{
	this->process_event(
		sanguis::client::events::connected()
	);
}

void
sanguis::client::machine::error_callback(
	fcppt::string const &_message,
	boost::system::error_code const &_error
)
{
	this->process_event(
		events::net_error(
			_message,
			_error
		)
	);
}

void
sanguis::client::machine::data_callback(
	alda::net::buffer::circular_receive::object &_data
)
{
	for(
		;;
	)
	{
		sanguis::messages::unique_ptr ret(
			sanguis::net::deserialize(
				_data
			)
		);

		if(
			!ret.get()
		)
			return;

		this->process_event(
			sanguis::client::events::message(
				std::move(
					ret
				)
			)
		);
	}
}
