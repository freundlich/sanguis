#ifndef SANGUIS_MESSAGES_REMOVE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_REMOVE_ID_HPP_INCLUDED

#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/make_message_id.hpp>
#include <sanguis/messages/types/message.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	sanguis::messages::make_message_id<
		sanguis::messages::types::message::remove_id
	>
>
remove_id;

}
}

#endif
