#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters.hpp>


sanguis::collision::world::body_parameters::body_parameters(
	sanguis::collision::center const _center,
	sanguis::collision::speed const _speed,
	sanguis::collision::radius const _radius,
	sanguis::collision::world::body_group const _collision_group,
	sanguis::collision::world::body_base &_body_base
)
:
	center_(
		_center
	),
	speed_(
		_speed
	),
	radius_(
		_radius
	),
	collision_group_(
		_collision_group
	),
	body_base_(
		_body_base
	)
{
}

sanguis::collision::center const
sanguis::collision::world::body_parameters::center() const
{
	return
		center_;
}

sanguis::collision::speed const
sanguis::collision::world::body_parameters::speed() const
{
	return
		speed_;
}

sanguis::collision::radius const
sanguis::collision::world::body_parameters::radius() const
{
	return
		radius_;
}

sanguis::collision::world::body_group
sanguis::collision::world::body_parameters::collision_group() const
{
	return
		collision_group_;
}

sanguis::collision::world::body_base &
sanguis::collision::world::body_parameters::body_base() const
{
	return
		body_base_;
}
