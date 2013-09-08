#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/aux/world/simple/body.hpp>
#include <sanguis/collision/aux/world/simple/body_remove_callback.hpp>
#include <sanguis/collision/aux/world/simple/body_unique_ptr.hpp>
#include <sanguis/collision/aux/world/simple/collides.hpp>
#include <sanguis/collision/aux/world/simple/ghost.hpp>
#include <sanguis/collision/aux/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/aux/world/simple/ghost_unique_ptr.hpp>
#include <sanguis/collision/aux/world/simple/object.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::aux::world::simple::object::object(
	sanguis::collision::world::parameters const &_parameters
)
:
	sanguis::collision::world::object(),
	body_collision_callback_(
		_parameters.body_collision_callback()
	),
	bodies_(),
	ghosts_()
{
}

sanguis::collision::aux::world::simple::object::~object()
{
}

sanguis::collision::world::body_unique_ptr
sanguis::collision::aux::world::simple::object::create_body(
	sanguis::collision::world::body_parameters const &_parameters
)
{
	sanguis::collision::aux::world::simple::body_unique_ptr result(
		fcppt::make_unique_ptr<
			sanguis::collision::aux::world::simple::body
		>(
			_parameters,
			sanguis::collision::aux::world::simple::body_remove_callback(
				std::bind(
					&sanguis::collision::aux::world::simple::object::remove_body,
					this,
					std::placeholders::_1
				)
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		bodies_.insert(
			result.get()
		).second
	);

	return
		std::move(
			result
		);
}

void
sanguis::collision::aux::world::simple::object::activate_body(
	sanguis::collision::world::body &_body
)
{
	sanguis::collision::aux::world::simple::body &body(
		fcppt::cast::static_downcast<
			sanguis::collision::aux::world::simple::body &
		>(
			_body
		)
	);

	for(
		auto ghost : ghosts_
	)
		ghost->update_body(
			body
		);
}

sanguis::collision::world::ghost_unique_ptr
sanguis::collision::aux::world::simple::object::create_ghost(
	sanguis::collision::world::ghost_parameters const &_parameters
)
{
	sanguis::collision::aux::world::simple::ghost_unique_ptr result(
		fcppt::make_unique_ptr<
			sanguis::collision::aux::world::simple::ghost
		>(
			_parameters,
			sanguis::collision::aux::world::simple::ghost_remove_callback(
				std::bind(
					&sanguis::collision::aux::world::simple::object::remove_ghost,
					this,
					std::placeholders::_1
				)
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		ghosts_.insert(
			result.get()
		).second
	);

	for(
		auto const body : bodies_
	)
		result->update_body(
			*body
		);

	return
		std::move(
			result
		);
}

void
sanguis::collision::aux::world::simple::object::update(
	sanguis::collision::duration const _duration
)
{
	for(
		auto body : bodies_
	)
		body->center(
			sanguis::collision::center(
				body->center().get()
				+
				body->speed().get()
				*
				_duration.count()
			)
		);

	for(
		auto const body1 : bodies_
	)
	{
		for(
			auto const body2 : bodies_
		)
			if(
				sanguis::collision::aux::world::simple::collides(
					*body1,
					*body2
				)
			)
				body_collision_callback_(
					body1->body_base(),
					body2->body_base()
				);

		for(
			auto const ghost : ghosts_
		)
			ghost->update_body(
				*body1
			);
	}
}

void
sanguis::collision::aux::world::simple::object::remove_body(
	sanguis::collision::aux::world::simple::body &_body
)
{
	FCPPT_ASSERT_ERROR(
		bodies_.erase(
			&_body
		)
		== 1u
	);

	for(
		auto const ghost : ghosts_
	)
		ghost->update_body(
			_body
		);
}

void
sanguis::collision::aux::world::simple::object::remove_ghost(
	sanguis::collision::aux::world::simple::ghost &_ghost
)
{
	FCPPT_ASSERT_ERROR(
		ghosts_.erase(
			&_ghost
		)
		== 1u
	);
}
