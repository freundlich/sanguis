#ifndef SANGUIS_MESSAGES_PLAYER_ATTACK_DEST_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_ATTACK_DEST_HPP_INCLUDED

#include <sanguis/messages/bind_player_message.hpp>
#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/vector2.hpp>
#include <sanguis/messages/roles/attack_dest.hpp>
#include <sanguis/messages/types/message.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

typedef sanguis::messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			sanguis::messages::bind_player_message<
				sanguis::messages::types::message::player_attack_dest
			>::type,
			majutsu::role<
				sanguis::messages::vector2,
				sanguis::messages::roles::attack_dest
			>
		>
	>
>::type player_attack_dest;

}
}

#endif
