#ifndef SANGUIS_COLLISION_AUX__WORLD_SIMPLE_GHOST_RESULT_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_SIMPLE_GHOST_RESULT_HPP_INCLUDED

#include <sanguis/collision/aux_/world/simple/ghost_result_fwd.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>


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

class ghost_result
{
public:
	ghost_result(
		sanguis::collision::world::body_enter_container &&,
		sanguis::collision::world::body_exit_container &&
	);

	sanguis::collision::world::body_enter_container &&
	release_body_enter();

	sanguis::collision::world::body_exit_container &&
	release_body_exit();
private:
	sanguis::collision::world::body_enter_container body_enter_;

	sanguis::collision::world::body_exit_container body_exit_;
};

}
}
}
}
}

#endif