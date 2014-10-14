#ifndef SANGUIS_COLLISION_AUX__WORLD_BODY_GROUP_RELATION_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_BODY_GROUP_RELATION_HPP_INCLUDED

#include <sanguis/collision/aux_/world/body_group_pair.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{

typedef
boost::mpl::map<
	sanguis::collision::aux_::world::body_group_pair<
		sanguis::collision::world::body_group::enemy,
		sanguis::collision::world::body_group::projectile_player
	>,
	sanguis::collision::aux_::world::body_group_pair<
		sanguis::collision::world::body_group::pickup,
		sanguis::collision::world::body_group::player
	>,
	sanguis::collision::aux_::world::body_group_pair<
		sanguis::collision::world::body_group::player,
		sanguis::collision::world::body_group::projectile_enemy
	>
>
body_group_relation;

}
}
}
}

#endif