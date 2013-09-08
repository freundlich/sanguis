#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_COLLISION_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_COLLISION_GROUPS_HPP_INCLUDED

#include <sanguis/collision/world/group_field_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

sanguis::collision::world::group_field const
collision_groups(
	sanguis::server::team
);

}
}
}
}

#endif
