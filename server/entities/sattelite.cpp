#include "sattelite.hpp"
#include "entity.hpp"
#include "../types.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

sanguis::server::entities::satellite::satellite(
	sanguis::server::entities::entity &_e)
:
	e(_e)
{
}

void
sanguis::server::entities::satellite::position_change(
	sge::collision::point const &)
{
}

sanguis::server::entities::entity &
sanguis::server::entities::satellite::entity()
{
	return e;
}

sanguis::server::entities::entity const &
sanguis::server::entities::satellite::entity() const
{
	return e;
}
