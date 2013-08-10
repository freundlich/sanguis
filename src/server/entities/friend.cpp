#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/load/friend_name.hpp>
#include <sanguis/messages/add_friend.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/entities/body_velocity_combiner.hpp>
#include <sanguis/server/entities/friend.hpp>
#include <sanguis/server/entities/circle_from_dim.hpp>
#include <sanguis/server/entities/default_solid.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/property/initial.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::friend_::friend_(
	sanguis::diff_clock const &_diff_clock,
	sanguis::friend_type const _ftype,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::damage::armor const &_armor,
	sanguis::server::health const _health,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::ai::create_function const &_ai,
	sanguis::server::weapons::unique_ptr &&_weapon
)
:
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::body_velocity_combiner(),
	sanguis::server::entities::with_ai(
		_ai,
		std::move(
			_weapon
		)
	),
	sanguis::server::entities::with_body(
		sanguis::server::entities::circle_from_dim(
			_load_context.entity_dim(
				sanguis::server::model_name(
					sanguis::load::friend_name(
						_ftype
					)
				)
			),
			sanguis::server::entities::default_solid()
		)
	),
	sanguis::server::entities::with_buffs(),
	sanguis::server::entities::with_id(
		_load_context.next_id()
	),
	sanguis::server::entities::with_health(
		_diff_clock,
		_health,
		_armor
	),
	sanguis::server::entities::with_links(),
	sanguis::server::entities::with_velocity(
		sanguis::server::entities::property::initial(
			sanguis::server::entities::property::initial::base(
				_movement_speed.get()
			),
			sanguis::server::entities::property::initial::current(
				0.f
			)
		),
		sanguis::server::direction(
			0.f
		)
	),
	ftype_(
		_ftype
	)
{
}

void
sanguis::server::entities::friend_::on_update()
{
	sanguis::server::entities::with_ai::on_update();

	sanguis::server::entities::with_buffs::on_update();

	sanguis::server::entities::with_health::on_update();
}

sanguis::server::team
sanguis::server::entities::friend_::team() const
{
	return sanguis::server::team::players;
}

sanguis::messages::unique_ptr
sanguis::server::entities::friend_::add_message(
	sanguis::server::player_id const
) const
{
	return
		sanguis::messages::create(
			sanguis::messages::add_friend(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->speed().get(),
				this->current_health().get(),
				this->max_health().get(),
				this->primary_weapon_type(),
				ftype_
			)
		);
}


sanguis::server::collision::group_vector
sanguis::server::entities::friend_::collision_groups() const
{
	return
		sanguis::server::collision::group_vector{
			sanguis::server::collision::group::player
		};
}
