#ifndef SANGUIS_MESSAGES_CHANGE_WEAPON_HPP_INCLUDED
#define SANGUIS_MESSAGES_CHANGE_WEAPON_HPP_INCLUDED

#include <sanguis/messages/roles/weapon.hpp>
#include <sanguis/messages/types/message.hpp>
#include <sanguis/messages/bind_entity_message.hpp>
#include <sanguis/messages/enum.hpp>
#include <sanguis/messages/make_class.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			messages::bind_entity_message<
				types::message::change_weapon
			>::type,
			majutsu::role<
				messages::enum_,
				roles::weapon
			>
		>
	>
>::type change_weapon;

}
}

#endif