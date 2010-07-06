#include "ias.hpp"
#include "change_simple.hpp"
#include "../entities/property/linear_change.hpp"
#include "../entities/with_weapon.hpp"

sanguis::server::perks::ias::ias()
:
	perk(
		perk_type::ias
	)
{}

void
sanguis::server::perks::ias::change(
	entities::base &entity_,
	level_diff const diff_
)
{
	perks::change_simple<
		entities::with_weapon
	>(
		&entities::property::linear_change,
		entity_,
		&entities::with_weapon::attack_speed,
		0.2f,
		diff_
	);
}

sanguis::server::perks::level_type
sanguis::server::perks::ias::max_level() const
{
	return 8;
}
