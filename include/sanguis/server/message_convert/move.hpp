#ifndef SANGUIS_SERVER_MESSAGE_CONVERT_MOVE_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERT_MOVE_HPP_INCLUDED

#include <sanguis/server/entities/with_velocity_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace message_convert
{

messages::auto_ptr
move(
	entities::with_velocity const &
);

}
}
}

#endif