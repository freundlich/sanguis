#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/grenade.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/grenade.hpp>
#include <sanguis/server/weapons/grenade_parameters.hpp>
#include <sanguis/server/weapons/insert_to_attack_result.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/make_aoe.hpp>
#include <sanguis/server/weapons/attributes/make_damage.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::grenade::grenade(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::weapons::grenade_parameters const &_parameters
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_random_generator,
		sanguis::weapon_type(
			sanguis::secondary_weapon_type::grenade
		),
		sanguis::server::weapons::attributes::optional_accuracy(),
		_parameters.range(),
		sanguis::server::weapons::attributes::optional_magazine_size(
			_parameters.magazine_size()
		),
		_parameters.base_cooldown(),
		_parameters.cast_point(),
		sanguis::server::weapons::optional_reload_time()
	),
	damage_(
		_parameters.damage()
	),
	aoe_(
		_parameters.aoe()
	)
{
}

sanguis::server::weapons::grenade::~grenade()
{
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::grenade::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	return
		sanguis::server::weapons::insert_to_attack_result(
			_attack.environment().insert(
				fcppt::make_unique_ptr<
					sanguis::server::entities::projectiles::grenade
				>(
					this->diff_clock(),
					_attack.environment().load_context(),
					_attack.team(),
					damage_.value(),
					aoe_.value(),
					_attack.target().get(),
					sanguis::server::direction(
						_attack.angle().get()
					)
				),
				sanguis::server::entities::insert_parameters(
					_attack.spawn_point(),
					_attack.angle()
				)
			)
		);
}

sanguis::weapon_attribute_vector
sanguis::server::weapons::grenade::attributes() const
{
	return
		sanguis::weapon_attribute_vector{
			sanguis::server::weapons::attributes::make_damage(
				damage_
			),
			sanguis::server::weapons::attributes::make_aoe(
				aoe_
			)
		};
}