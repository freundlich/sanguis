#include "satellite.hpp"

sanguis::server::collision::satellite::satellite(
	collision::base &_base
)
:
	base_(_base)
{
}

sanguis::server::collision::satellite::~satellite()
{
}

void
sanguis::server::collision::satellite::position_change(
	sge::collision::point const &
)
{
}

void
sanguis::server::collision::satellite::velocity_change(
	sge::collision::point const &
)
{
}

sanguis::server::collision::base &
sanguis::server::collision::satellite::base()
{
	return base_;
}

sanguis::server::collision::base const &
sanguis::server::collision::satellite::base() const
{
	return base_;
}