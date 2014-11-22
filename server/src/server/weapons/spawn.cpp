#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/creator/tile_is_visible.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_health.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/attack.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/parameters.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/spawn.hpp>
#include <sanguis/server/weapons/spawn_parameters.hpp>
#include <sanguis/server/weapons/spawn_weapon.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/magazine_size.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/algorithm/join.hpp>


sanguis::server::weapons::spawn::spawn(
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _weapon_type,
	sanguis::server::weapons::spawn_weapon const &_spawn_weapon,
	sanguis::server::weapons::range const _range,
	sanguis::server::weapons::backswing_time const _backswing_time,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::reload_time const _reload_time
)
:
	sanguis::server::weapons::spawn{
		sanguis::server::weapons::spawn_parameters{
			sanguis::server::weapons::parameters{
				_random_generator,
				_weapon_type,
				sanguis::server::weapons::attributes::optional_accuracy(),
				_range,
				sanguis::server::weapons::attributes::optional_magazine_size{
					sanguis::server::weapons::attributes::magazine_size{
						sanguis::server::weapons::magazine_size{
							1u
						}
					}
				},
				_backswing_time,
				_cast_point,
				sanguis::server::weapons::optional_reload_time{
					_reload_time
				}
			},
			_spawn_weapon
		}
	}
{
}

sanguis::server::weapons::spawn::~spawn()
{
}

sanguis::server::weapons::spawn::spawn(
	sanguis::server::weapons::spawn_parameters const &_spawn_parameters
)
:
	sanguis::server::weapons::weapon{
		_spawn_parameters.parameters()
	},
	spawn_weapon_{
		_spawn_parameters.spawn_weapon()
	},
	attributes_(
		spawn_weapon_.get()()->attributes()
	),
	spawned_()
{
}

sanguis::server::weapons::spawn_parameters
sanguis::server::weapons::spawn::spawn_parameters() const
{
	return
		sanguis::server::weapons::spawn_parameters{
			this->parameters(),
			spawn_weapon_
		};
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::spawn::do_attack(
	sanguis::server::weapons::attack const &_attack
)
{
	return
		!sanguis::creator::tile_is_visible(
			_attack.environment().grid(),
			sanguis::server::world::center_to_grid_pos(
				sanguis::server::center{
					_attack.target().get()
				}
			),
			sanguis::server::world::center_to_grid_pos(
				this->owner().center()
			)
		)
		?
			sanguis::server::weapons::attack_result::failure
		:
			fcppt::maybe(
				this->do_spawn(
					_attack,
					spawn_weapon_
				),
				[]{
					return
						sanguis::server::weapons::attack_result::failure;
				},
				[
					this
				](
					sanguis::server::entities::base &_inserted
				)
				{
					this->kill_spawned();

					spawned_ =
						dynamic_cast<
							sanguis::server::entities::ifaces::with_links &
						>(
							_inserted
						).link();

					return
						sanguis::server::weapons::attack_result::success;
				}
			)
		;
}

sanguis::weapon_attribute_vector
sanguis::server::weapons::spawn::attributes() const
{
	return
		fcppt::algorithm::join(
			this->extra_attributes(),
			attributes_
		);
}

void
sanguis::server::weapons::spawn::owner_lost()
{
	this->kill_spawned();
}

void
sanguis::server::weapons::spawn::kill_spawned()
{
	fcppt::maybe_void(
		spawned_.get(),
		[](
			sanguis::server::entities::with_links &_spawned
		)
		{
			dynamic_cast<
				sanguis::server::entities::ifaces::with_health &
			>(
				_spawned
			).kill();
		}
	);
}
