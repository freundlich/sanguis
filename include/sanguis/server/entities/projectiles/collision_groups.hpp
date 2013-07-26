#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_COLLISION_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_COLLISION_GROUPS_HPP_INCLUDED

#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/collision/group_vector.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

sanguis::server::collision::group_vector
collision_groups(
	sanguis::server::team
);

}
}
}
}

#endif