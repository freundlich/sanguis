#include "create_parameters.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::collision::create_parameters::create_parameters(
	pos_type const &_center,
	pos_type const &_speed
)
:
	center_(_center),
	speed_(_speed)
{}

sanguis::server::pos_type const
sanguis::server::collision::create_parameters::center() const
{
	return center_;
}

sanguis::server::pos_type const
sanguis::server::collision::create_parameters::speed() const
{
	return speed_;
}