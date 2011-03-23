#ifndef SANGUIS_MESSAGES_PLAYER_CHOOSE_PERK_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_CHOOSE_PERK_HPP_INCLUDED

#include "roles/perk.hpp"
#include "types/message.hpp"
#include "bind_player_message.hpp"
#include "enum.hpp"
#include "make_class.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector2<
		bind_player_message<
			types::message::player_choose_perk
		>::type,
		majutsu::role<
			enum_,
			roles::perk
		>
	>
> player_choose_perk_elements;

typedef make_class<
	player_choose_perk_elements
>::type player_choose_perk;

}
}

#endif