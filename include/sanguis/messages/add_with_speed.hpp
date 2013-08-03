#ifndef SANGUIS_MESSAGES_ADD_WITH_SPEED_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_WITH_SPEED_HPP_INCLUDED

#include <sanguis/messages/add_elements_base.hpp>
#include <sanguis/messages/vector2.hpp>
#include <sanguis/messages/roles/speed.hpp>
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
majutsu::composite<
	boost::mpl::vector2<
		sanguis::messages::add_elements_base,
		majutsu::role<
			sanguis::messages::vector2,
			sanguis::messages::roles::speed
		>
	>
>
add_with_speed;

}
}

#endif
