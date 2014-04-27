#ifndef SANGUIS_MESSAGES_SERVER_UNPAUSE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_UNPAUSE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/make_class_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
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
		boost::mpl::vector1<
			sanguis::messages::server::types::make_message_id<
				sanguis::messages::server::types::message::unpause
			>
		>
	>
>
unpause;

}
}
}

#endif