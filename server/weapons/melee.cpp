#include "melee.hpp"
#include "delayed_attack.hpp"
#include "../entities/entity.hpp"
#include "../entities/projectiles/melee.hpp"

sanguis::server::weapons::melee::melee(
	environment const &env,
	weapon_type::type const type_,
	space_unit const range,
	time_type const base_cooldown,
	space_unit const damage)
: weapon(
	env,
	type_,
	range,
	unlimited_magazine,
	base_cooldown,
	static_cast<time_type>(
		0),
	static_cast<time_type>(
		0)),
  damage(damage)
{}

void sanguis::server::weapons::melee::do_attack(
	delayed_attack const &a)
{
	insert(
		entities::auto_ptr(
			new entities::projectiles::melee(
				get_environment(),
				a.dest(),
				a.team(),
				damage)));
}
