#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/world/body_enter_callback.hpp>
#include <sanguis/collision/world/body_exit_callback.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/collision/world/object.hpp>
#include <fcppt/assert/pre.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/collision/ghost.hpp>


sanguis::server::collision::ghost::ghost(
	sanguis::collision::world::group_field const &_collision_groups,
	sanguis::collision::world::body_enter_callback const &_body_enter_callback,
	sanguis::collision::world::body_exit_callback const &_body_exit_callback,
	sanguis::server::radius const _radius
)
:
	collision_groups_(
		_collision_groups
	),
	body_enter_callback_(
		_body_enter_callback
	),
	body_exit_callback_(
		_body_exit_callback
	),
	radius_(
		_radius
	),
	impl_()
{
}

sanguis::server::collision::ghost::~ghost()
{
}

void
sanguis::server::collision::ghost::transfer(
	sanguis::collision::world::object &_world,
	sanguis::server::center const _center
)
{
	this->destroy();

	impl_.take(
		_world.create_ghost(
			sanguis::collision::world::ghost_parameters(
				sanguis::collision::center(
					_center.get()
				),
				sanguis::collision::radius(
					radius_.get()
				),
				body_enter_callback_,
				body_exit_callback_,
				collision_groups_
			)
		)
	);
}

void
sanguis::server::collision::ghost::destroy()
{
	impl_.reset();
}

void
sanguis::server::collision::ghost::center(
	sanguis::server::center const _center
)
{
	FCPPT_ASSERT_PRE(
		impl_
	);

	impl_->center(
		sanguis::collision::center(
			_center.get()
		)
	);
}
