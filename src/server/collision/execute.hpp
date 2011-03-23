#ifndef SANGUIS_SERVER_COLLISION_EXECUTE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_EXECUTE_HPP_INCLUDED

#include "execute_function.hpp"
#include <sge/collision/satellite_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

void
execute(
	sge::collision::satellite &,
	sge::collision::satellite &,
	execute_function const &
);

}
}
}

#endif