#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_base_ref.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/to_center.hpp>
#include <sanguis/server/collision/to_radius.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/object_impl.hpp>


sanguis::server::collision::ghost::ghost(
	sanguis::collision::world::ghost_base_ref const _ghost_base,
	sanguis::collision::world::ghost_group const _collision_group,
	sanguis::server::radius const _radius
)
:
	ghost_base_(
		_ghost_base
	),
	collision_group_(
		_collision_group
	),
	radius_(
		_radius
	),
	impl_()
{
}

sanguis::server::collision::ghost::ghost(
	ghost &&
)
noexcept
= default;

sanguis::server::collision::ghost &
sanguis::server::collision::ghost::operator=(
	ghost &&
)
noexcept
= default;

sanguis::server::collision::ghost::~ghost()
= default;

sanguis::collision::world::body_enter_container
sanguis::server::collision::ghost::transfer(
	sanguis::collision::world::object &_world,
	sanguis::server::center const &_center
)
{
	FCPPT_ASSERT_PRE(
		!impl_.has_value()
	);

	sanguis::collision::world::ghost_unique_ptr const &new_ghost(
		fcppt::optional::assign(
			impl_,
			_world.create_ghost(
				sanguis::collision::world::ghost_parameters(
					sanguis::server::collision::to_center(
						_center
					),
					sanguis::server::collision::to_radius(
						radius_
					),
					collision_group_,
					ghost_base_
				)
			)
		)
	);

	return
		_world.activate_ghost(
			fcppt::make_ref(
				*new_ghost
			)
		);
}

sanguis::collision::world::body_exit_container
sanguis::server::collision::ghost::destroy(
	sanguis::collision::world::object &_world
)
{
	sanguis::collision::world::body_exit_container result(
		_world.deactivate_ghost(
			fcppt::make_ref(
				*FCPPT_ASSERT_OPTIONAL_ERROR(
					impl_
				)
			)
		)
	);

	impl_ =
		optional_ghost_unique_ptr();

	return
		result;
}

void
sanguis::server::collision::ghost::center(
	sanguis::server::center const &_center
)
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		impl_
	)->center(
		sanguis::server::collision::to_center(
			_center
		)
	);
}
