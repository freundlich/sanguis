#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/world/body_enter_callback.hpp>
#include <sanguis/collision/world/body_exit_callback.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>


sanguis::collision::world::ghost_parameters::ghost_parameters(
	sanguis::collision::center const _center,
	sanguis::collision::radius const _radius,
	sanguis::collision::world::body_enter_callback const &_body_enter_callback,
	sanguis::collision::world::body_exit_callback const &_body_exit_callback,
	sanguis::collision::world::ghost_group const _collision_group
)
:
	center_(
		_center
	),
	radius_(
		_radius
	),
	body_enter_callback_(
		_body_enter_callback
	),
	body_exit_callback_(
		_body_exit_callback
	),
	collision_group_(
		_collision_group
	)
{
}

sanguis::collision::center const
sanguis::collision::world::ghost_parameters::center() const
{
	return
		center_;
}

sanguis::collision::radius const
sanguis::collision::world::ghost_parameters::radius() const
{
	return
		radius_;
}

sanguis::collision::world::body_enter_callback const &
sanguis::collision::world::ghost_parameters::body_enter_callback() const
{
	return
		body_enter_callback_;
}

sanguis::collision::world::body_exit_callback const &
sanguis::collision::world::ghost_parameters::body_exit_callback() const
{
	return
		body_exit_callback_;
}

sanguis::collision::world::ghost_group
sanguis::collision::world::ghost_parameters::collision_group() const
{
	return
		collision_group_;
}
