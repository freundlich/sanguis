#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/rocket.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/rocket_launcher.hpp>
#include <sanguis/server/weapons/rocket_launcher_parameters.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/accuracy.hpp>
#include <sanguis/server/weapons/attributes/magazine_size.hpp>
#include <sanguis/server/weapons/attributes/make_aoe.hpp>
#include <sanguis/server/weapons/attributes/make_damage.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::rocket_launcher::rocket_launcher(
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _weapon_type,
	sanguis::server::weapons::rocket_launcher_parameters const &_parameters
)
:
	sanguis::server::weapons::weapon(
		_random_generator,
		_weapon_type,
		sanguis::server::weapons::attributes::optional_accuracy(
			sanguis::server::weapons::attributes::accuracy(
				_parameters.accuracy()
			)
		),
		_parameters.range(),
		sanguis::server::weapons::attributes::optional_magazine_size(
			sanguis::server::weapons::attributes::magazine_size(
				_parameters.magazine_size()
			)
		),
		_parameters.base_cooldown(),
		_parameters.cast_point(),
		sanguis::server::weapons::optional_reload_time(
			_parameters.reload_time()
		)
	),
	damage_(
		_parameters.damage()
	),
	aoe_(
		_parameters.aoe()
	)
{
}

sanguis::server::weapons::rocket_launcher::~rocket_launcher()
{
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::rocket_launcher::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	sanguis::server::environment::insert_no_result(
		_attack.environment(),
		fcppt::make_unique_ptr<
			sanguis::server::entities::projectiles::rocket
		>(
			_attack.environment().load_context(),
			_attack.team(),
			damage_.value(),
			aoe_.value(),
			sanguis::server::direction(
				_attack.angle().get()
			)
		),
		sanguis::server::entities::insert_parameters(
			_attack.spawn_point(),
			_attack.angle()
		)
	);

	return
		sanguis::server::weapons::attack_result::success;
}

sanguis::weapon_attribute_vector
sanguis::server::weapons::rocket_launcher::attributes() const
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
