#ifndef SANGUIS_COLLISION_WORLD_BODY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/mass.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class body_parameters
{
	FCPPT_NONASSIGNABLE(
		body_parameters
	);
public:
	SANGUIS_COLLISION_SYMBOL
	body_parameters(
		sanguis::collision::center,
		sanguis::collision::speed,
		sanguis::collision::radius,
		sanguis::collision::mass,
		sanguis::collision::world::body_group,
		sanguis::collision::world::body_base &
	);

	sanguis::collision::center const
	center() const;

	sanguis::collision::speed const
	speed() const;

	sanguis::collision::radius const
	radius() const;

	sanguis::collision::mass const
	mass() const;

	sanguis::collision::world::body_group
	collision_group() const;

	sanguis::collision::world::body_base &
	body_base() const;
private:
	sanguis::collision::center const center_;

	sanguis::collision::speed const speed_;

	sanguis::collision::radius const radius_;

	sanguis::collision::mass const mass_;

	sanguis::collision::world::body_group const collision_group_;

	sanguis::collision::world::body_base &body_base_;
};

}
}
}

#endif
