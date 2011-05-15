#ifndef SANGUIS_MESSAGES_CHANGE_WORLD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CHANGE_WORLD_HPP_INCLUDED

#include "roles/generator_name.hpp"
#include "types/message.hpp"
#include "make_class.hpp"
#include "make_message_id.hpp"
#include "seed.hpp"
#include "string.hpp"
#include "world_id.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector4<
			messages::make_message_id<
				types::message::change_world
			>::type,
			majutsu::role<
				messages::world_id
			>,
			majutsu::role<
				messages::seed
			>,
			majutsu::role<
				messages::string,
				roles::generator_name
			>
		>
	>
>::type change_world;

}
}

#endif
