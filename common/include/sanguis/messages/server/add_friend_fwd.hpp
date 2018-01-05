#ifndef SANGUIS_MESSAGES_SERVER_ADD_FRIEND_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_FRIEND_FWD_HPP_INCLUDED

#include <sanguis/friend_type_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/roles/friend_type.hpp>
#include <sanguis/messages/server/parts/add_actor_fwd.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/mpl/flatten.hpp>
#include <fcppt/mpl/to_brigand.hpp>
#include <fcppt/record/element_fwd.hpp>
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
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::add_friend
	>,
	alda::bindings::record<
		fcppt::mpl::to_brigand<
			fcppt::mpl::flatten<
				boost::mpl::vector3<
					sanguis::messages::server::parts::entity_id,
					sanguis::messages::server::parts::add_actor,
					fcppt::record::element<
						sanguis::messages::roles::friend_type,
						sanguis::messages::adapted_types::enum_<
							sanguis::friend_type
						>
					>
				>
			>
		>
	>
>
add_friend;

}
}
}

#endif
