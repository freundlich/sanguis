#ifndef SANGUIS_MESSAGES_PLAYER_CHEAT_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_CHEAT_HPP_INCLUDED

#include <sanguis/cheat_type.hpp>
#include <sanguis/messages/bind_player_message.hpp>
#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/enum.hpp>
#include <sanguis/messages/roles/cheat.hpp>
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

typedef
sanguis::messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			sanguis::messages::bind_player_message<
				sanguis::messages::types::message::player_cheat
			>,
			majutsu::role<
				sanguis::messages::enum_<
					sanguis::cheat_type
				>,
				sanguis::messages::roles::cheat
			>
		>
	>
>
player_cheat;

}
}

#endif
