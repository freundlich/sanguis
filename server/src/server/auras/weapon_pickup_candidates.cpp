#include <sanguis/optional_aura_type.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/server/add_weapon_pickup_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_weapon_pickup_callback.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/weapon_pickup_candidates.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <fcppt/cast/static_downcast.hpp>


sanguis::server::auras::weapon_pickup_candidates::weapon_pickup_candidates(
	sanguis::server::radius const _radius,
	sanguis::server::add_weapon_pickup_callback const &_add,
	sanguis::server::remove_weapon_pickup_callback const &_remove
)
:
	sanguis::server::auras::aura(
		_radius,
		sanguis::collision::world::ghost_group::weapon_pickup_sight
	),
	add_(
		_add
	),
	remove_(
		_remove
	)
{
}

sanguis::server::auras::weapon_pickup_candidates::~weapon_pickup_candidates()
{
}

sanguis::optional_aura_type
sanguis::server::auras::weapon_pickup_candidates::type() const
{
	return
		sanguis::optional_aura_type();
}

void
sanguis::server::auras::weapon_pickup_candidates::enter(
	sanguis::server::entities::with_body &_body,
	sanguis::collision::world::created
)
{
	add_.get()(
		fcppt::cast::static_downcast<
			sanguis::server::entities::pickups::weapon &
		>(
			_body
		)
	);
}

void
sanguis::server::auras::weapon_pickup_candidates::leave(
	sanguis::server::entities::with_body &_body
)
{
	remove_.get()(
		fcppt::cast::static_downcast<
			sanguis::server::entities::pickups::weapon &
		>(
			_body
		)
	);
}
