#ifndef SANGUIS_COLLISION_AUX__WORLD_SIMPLE_GROUPS_COLLIDE_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_SIMPLE_GROUPS_COLLIDE_HPP_INCLUDED

#include <sanguis/collision/world/group_field_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{
namespace simple
{

bool
groups_collide(
	sanguis::collision::world::group_field const &,
	sanguis::collision::world::group_field const &
);

}
}
}
}
}

#endif