#include <sanguis/load/weapon_pickup_name.hpp>
#include <sanguis/messages/add_weapon_pickup.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/collision/group.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/entities/circle_from_dim.hpp>
#include <sanguis/server/entities/nonsolid.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::pickups::weapon::weapon(
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::server::weapons::unique_ptr &&_weapon
)
:
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::with_body(
		sanguis::server::entities::circle_from_dim(
			_load_context.entity_dim(
				sanguis::server::model_name(
					sanguis::load::weapon_pickup_name(
						_weapon->type()
					)
				)
			),
			sanguis::server::entities::nonsolid()
		)
	),
	sanguis::server::entities::with_id(
		_load_context.next_id()
	),
	sanguis::server::entities::with_links(),
	team_(
		_team
	),
	weapon_(
		std::move(
			_weapon
		)
	)
{
}

sanguis::server::entities::pickups::weapon::~weapon()
{
}

sanguis::server::weapons::unique_ptr
sanguis::server::entities::pickups::weapon::obtain()
{
	return
		std::move(
			weapon_
		);
}

bool
sanguis::server::entities::pickups::weapon::dead() const
{
	return
		!weapon_;
}

sanguis::server::team
sanguis::server::entities::pickups::weapon::team() const
{
	return
		team_;
}

sanguis::server::collision::group_vector
sanguis::server::entities::pickups::weapon::collision_groups() const
{
	return
		sanguis::server::collision::group_vector{
			sanguis::server::collision::group::weapon_pickup
		};
}

sanguis::messages::unique_ptr
sanguis::server::entities::pickups::weapon::add_message(
	sanguis::server::player_id const
) const
{
	return
		sanguis::messages::create(
			sanguis::messages::add_weapon_pickup(
				this->id(),
				this->center().get(),
				this->angle().get(),
				weapon_->type()
			)
		);
}
