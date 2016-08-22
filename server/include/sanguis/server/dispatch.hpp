#ifndef SANGUIS_SERVER_DISPATCH_HPP_INCLUDED
#define SANGUIS_SERVER_DISPATCH_HPP_INCLUDED

#include <sanguis/messages/call/dispatch.hpp>
#include <sanguis/messages/client/call/object.hpp>
#include <sanguis/server/dispatch_default_function.hpp>
#include <sanguis/server/message_function.hpp>
#include <sanguis/server/events/message.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

template<
	typename MessageTypes,
	typename State
>
boost::statechart::result
dispatch(
	State &_state,
	sanguis::server::events::message const &_message,
	sanguis::server::dispatch_default_function const &_handle_default_msg
)
{
	typedef
	sanguis::server::message_function<
		State
	>
	function_type;

	static
	sanguis::messages::client::call::object<
		MessageTypes,
		function_type
	>
	dispatcher;

	function_type function(
		_state,
		_message.id()
	);

	return
		sanguis::messages::call::dispatch(
			dispatcher,
			function,
			_message,
			[
				&_message,
				&_handle_default_msg
			](
				auto const &_inner_message
			)
			{
				return
					_handle_default_msg(
						_message.id(),
						_inner_message
					);
			}
		);
}

}
}

#endif
