#include <sanguis/client/states/menu.hpp>
#include <sanguis/client/states/waiting_for_player.hpp>
#include <sanguis/client/states/log_location.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/menu.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/client_info.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/log_parameters.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <ostream>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::client::states::log_location()
		/
		FCPPT_TEXT("menu")
	)
);

}

sanguis::client::states::menu::menu(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	menu_(
		context<machine>().settings(),
		context<machine>().gui(),
		gui::menu::callbacks::object(
			std::bind(
				&machine::connect,
				&context<machine>(),
				std::placeholders::_1,
				std::placeholders::_2
			),
			std::bind(
				&machine::disconnect,
				&context<machine>()
			),
			std::bind(
				&machine::quickstart,
				&context<machine>(),
				std::placeholders::_1
			),
			std::bind(
				&machine::quit,
				&context<machine>()
			)
		)
	)
{
}

sanguis::client::states::menu::~menu()
{
}

boost::statechart::result
sanguis::client::states::menu::react(
	events::tick const &_event
)
{
	menu_.process(
		_event.delta()
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(
	events::render const &_event
)
{
	menu_.draw(
		_event.context()
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(
	events::message const &_message
)
{
	static messages::call::object<
		boost::mpl::vector1<
			messages::connect_state
		>,
		menu
	>::type dispatcher;

	return
		dispatcher(
			*_message.value(),
			*this,
			std::bind(
				&menu::handle_default_msg,
				this,
				std::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::client::states::menu::react(
	events::connected const &
)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("menu: connect")
	);

	context<machine>().send(
		*messages::create(
			messages::client_info(
				sge::charconv::fcppt_string_to_utf8(
					FCPPT_TEXT("player1") // TODO!
				)
			)
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(
	events::net_error const &_error
)
{
	menu_.connection_error(
		fcppt::from_std_string(
			_error.code().message()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::handle_default_msg(
	messages::base const &
)
{
	return forward_event();
}

boost::statechart::result
sanguis::client::states::menu::operator()(
	messages::connect_state const &_state // TODO: do we need this?
)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("Received connect_state")
	);

	return transit<waiting_for_player>();
}
