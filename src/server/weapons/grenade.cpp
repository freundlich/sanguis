#include "grenade.hpp"
#include "delayed_attack.hpp"
#include "../entities/insert_parameters.hpp"
#include "../entities/projectiles/grenade.hpp"
#include "../environment/object.hpp"
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::weapons::grenade::grenade(
	weapon_type::type const _type,
	weapons::base_cooldown const _base_cooldown,
	weapons::damage const _damage,
	weapons::aoe const _aoe,
	weapons::cast_point const _cast_point,
	weapons::reload_time const _reload_time
)
:
	weapon(
		_type,
		weapons::range(1000), // FIXME
		weapons::magazine_size(1),
		weapons::magazine_count(1),
		_base_cooldown,
		_cast_point,
		_reload_time
	),
	damage_(_damage),
	aoe_(_aoe)
{
}

sanguis::server::weapons::grenade::~grenade()
{
}

void
sanguis::server::weapons::grenade::do_attack(
	delayed_attack const &_attack
)
{
	_attack.environment()->insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::projectiles::grenade
			>(
				_attack.environment()->load_context(),
				_attack.team(),
				server::damage::unit(
					damage_
				),
				aoe_.get(),
				_attack.dest(),
				_attack.angle()
			)
		),
		entities::insert_parameters(
			_attack.spawn_point(),
			_attack.angle()
		)
	);
}