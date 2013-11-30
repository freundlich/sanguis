#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/rocket.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/make_attribute.hpp>
#include <sanguis/server/weapons/optional_magazine_size.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/rocket_launcher.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>


sanguis::server::weapons::rocket_launcher::rocket_launcher(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _type,
	sanguis::server::weapons::accuracy const _accuracy,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::damage const _damage,
	sanguis::server::weapons::aoe const _aoe,
	sanguis::server::weapons::magazine_size const _magazine_size,
	sanguis::server::weapons::reload_time const _reload_time,
	sanguis::server::weapons::range const _range
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_random_generator,
		_type,
		_accuracy,
		_range,
		sanguis::server::weapons::optional_magazine_size(
			_magazine_size
		),
		_base_cooldown,
		_cast_point,
		sanguis::server::weapons::optional_reload_time(
			_reload_time
		)
	),
	damage_(
		_damage
	),
	aoe_(
		_aoe
	)
{
}

sanguis::server::weapons::rocket_launcher::~rocket_launcher()
{
}

bool
sanguis::server::weapons::rocket_launcher::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	sanguis::server::environment::insert_no_result(
		_attack.environment(),
		fcppt::make_unique_ptr<
			sanguis::server::entities::projectiles::rocket
		>(
			this->diff_clock(),
			_attack.environment().load_context(),
			_attack.team(),
			damage_,
			sanguis::server::radius(
				aoe_.get()
			),
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
		true;
}

sanguis::string_vector
sanguis::server::weapons::rocket_launcher::attributes() const
{
	return
		sanguis::string_vector{
			sanguis::server::weapons::make_attribute(
				FCPPT_TEXT("damage"),
				fcppt::insert_to_fcppt_string(
					damage_
				)
			),
			sanguis::server::weapons::make_attribute(
				FCPPT_TEXT("aoe"),
				fcppt::insert_to_fcppt_string(
					aoe_
				)
			)
		};
}
