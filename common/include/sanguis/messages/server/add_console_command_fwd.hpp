#ifndef SANGUIS_MESSAGES_SERVER_ADD_CONSOLE_COMMAND_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_CONSOLE_COMMAND_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/roles/command_description.hpp>
#include <sanguis/messages/roles/command_name.hpp>
#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/make_class_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector3<
			sanguis::messages::server::types::make_message_id<
				sanguis::messages::server::types::message::add_console_command
			>,
			majutsu::role<
				sanguis::messages::adapted_types::string,
				sanguis::messages::roles::command_name
			>,
			majutsu::role<
				sanguis::messages::adapted_types::string,
				sanguis::messages::roles::command_description
			>
		>
	>
>
add_console_command;

}
}
}

#endif