#ifndef SANGUIS_MESSAGES_SERVER_TYPES_WEAPON_ATTRIBUTE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_TYPES_WEAPON_ATTRIBUTE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/optional_weapon_attribute_value_fwd.hpp>
#include <sanguis/messages/adapted_types/weapon_attribute_type_fwd.hpp>
#include <sanguis/messages/adapted_types/weapon_attribute_value_fwd.hpp>
#include <sanguis/messages/roles/weapon_attribute_base.hpp>
#include <sanguis/messages/roles/weapon_attribute_extra.hpp>
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
namespace types
{

typedef
alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector3<
			majutsu::role<
				sanguis::messages::adapted_types::weapon_attribute_type
			>,
			majutsu::role<
				sanguis::messages::adapted_types::weapon_attribute_value,
				sanguis::messages::roles::weapon_attribute_base
			>,
			majutsu::role<
				sanguis::messages::adapted_types::optional_weapon_attribute_value,
				sanguis::messages::roles::weapon_attribute_extra
			>
		>
	>
>
weapon_attribute;

}
}
}
}

#endif