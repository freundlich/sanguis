#include "ims.hpp"
#include "../entities/property.hpp"
#include "../entities/entity.hpp"

void sanguis::server::perks::ims::do_apply(
	entities::entity &e,
	time_type,
	environment const &)
{
	e.property(
		entities::property_type::movement_speed)
		.multiply_max(factor());
}

bool sanguis::server::perks::ims::can_raise_level() const
{
	return true;
}

sanguis::server::space_unit
sanguis::server::perks::ims::factor() const
{
	return static_cast<space_unit>(level())
		* static_cast<space_unit>(0.1);
}
