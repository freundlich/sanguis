#include <sanguis/optional_aura_type.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/server/add_sight_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_sight_callback.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/update_sight.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic_cross.hpp>
#include <fcppt/optional/maybe_void.hpp>


sanguis::server::auras::update_sight::update_sight(
	sanguis::server::radius const _radius,
	sanguis::server::add_sight_callback const &_add,
	sanguis::server::remove_sight_callback const &_remove
)
:
	sanguis::server::auras::aura(
		_radius,
		sanguis::collision::world::ghost_group::player_sight
	),
	add_(
		_add
	),
	remove_(
		_remove
	)
{
}

sanguis::server::auras::update_sight::~update_sight()
{
}

sanguis::optional_aura_type
sanguis::server::auras::update_sight::type() const
{
	return
		sanguis::optional_aura_type();
}

void
sanguis::server::auras::update_sight::enter(
	sanguis::server::entities::with_body &_entity,
	sanguis::collision::world::created const _created
)
{
	fcppt::optional::maybe_void(
		fcppt::cast::dynamic_cross<
			sanguis::server::entities::with_id const
		>(
			_entity
		),
		[
			this,
			_created
		](
			fcppt::reference<
				sanguis::server::entities::with_id const
			> const _with_id
		)
		{
			add_(
				_with_id.get(),
				_created
			);
		}
	);
}

void
sanguis::server::auras::update_sight::leave(
	sanguis::server::entities::with_body &_entity
)
{
	fcppt::optional::maybe_void(
		fcppt::cast::dynamic_cross<
			sanguis::server::entities::with_id const
		>(
			_entity
		),
		[
			this
		](
			fcppt::reference<
				sanguis::server::entities::with_id const
			> const _with_id
		)
		{
			remove_(
				_with_id.get()
			);
		}
	);
}
