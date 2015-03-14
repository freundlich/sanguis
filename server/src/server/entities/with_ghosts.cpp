#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/remove_from_world_result.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/environment/optional_object_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_ghosts::with_ghosts()
:
	sanguis::server::entities::base(),
	ghosts_()
{
}

sanguis::server::entities::with_ghosts::~with_ghosts()
{
}

void
sanguis::server::entities::with_ghosts::add_ghost(
	sanguis::server::collision::ghost &&_ghost
)
{
	ghosts_.push_back(
		std::move(
			_ghost
		)
	);

	sanguis::server::environment::optional_object_ref const env(
		this->environment()
	);

	if(
		env
	)
		this->insert_ghost(
			ghosts_.back(),
			env->collision_world()
		);
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::with_ghosts::on_transfer(
	sanguis::server::entities::transfer_parameters const &_params
)
{
	for(
		auto &ghost
		:
		ghosts_
	)
		this->insert_ghost(
			ghost,
			_params.world()
		);

	// TODO: Return state here
	return
		sanguis::server::entities::optional_transfer_result(
			sanguis::server::entities::transfer_result()
		);
}

sanguis::server::entities::remove_from_world_result
sanguis::server::entities::with_ghosts::remove_from_world()
{
	// FIXME: Remove ghosts properly
	for(
		auto &ghost
		:
		ghosts_
	)
		ghost.destroy();

	return
		sanguis::server::entities::remove_from_world_result();
}

void
sanguis::server::entities::with_ghosts::update_center(
	sanguis::server::center const &_center
)
{
	for(
		auto &ghost
		:
		ghosts_
	)
		ghost.center(
			_center
		);
}

void
sanguis::server::entities::with_ghosts::insert_ghost(
	sanguis::server::collision::ghost &_ghost,
	sanguis::collision::world::object &_world
)
{
	_ghost.transfer(
		_world,
		this->center()
	);
}
