#include "aoe_damage.hpp"
#include "../../auras/burn.hpp"
#include "../../environment/object.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>

sanguis::server::entities::projectiles::aoe_damage::aoe_damage(
	team::type const _team,
	space_unit const _radius,
	damage::unit const _damage_per_pulse,
	unsigned const _max_pulses,
	time_type const _pulse_diff,
	damage::array const &_damage_values
)
:
	aoe_projectile(
		aoe_projectile_type::aoe_damage,
		_team,
		entities::movement_speed(0),
		dim_type(
			_radius * static_cast<space_unit>(2),
			_radius * static_cast<space_unit>(2)
		),
		life_time(
			_pulse_diff
			* static_cast<
				time_type
			>(
				_max_pulses
			)
		),
		indeterminate::yes,
		_radius,
		static_cast<space_unit>(0)
	)
{
	add_aura(
		auras::unique_ptr(
			fcppt::make_unique_ptr<
				auras::burn
			>(
				_radius,
				_team,
				_damage_per_pulse,
				_pulse_diff,
				_damage_values
			)
		)
	);
}

void
sanguis::server::entities::projectiles::aoe_damage::on_update(
	time_type const time_
)
{
	projectile::on_update(
		time_
	);

	with_auras::on_update(
		time_
	);
}

void
sanguis::server::entities::projectiles::aoe_damage::do_damage(
	with_health &
)
{}
