#include "control_environment.hpp"
#include "object.hpp"
#include "../translate/vector_from_client.hpp"
#include "../vector2.hpp"
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::client::draw2d::scene::control_environment::control_environment(
	draw2d::scene::object &_object
)
:
	object_(_object)
{
}

sanguis::client::draw2d::scene::control_environment::~control_environment()
{
}

sanguis::client::control::attack_dest const
sanguis::client::draw2d::scene::control_environment::translate_attack_dest(
	client::control::cursor_position const &_cursor_position
) const
{
	return
		draw2d::translate::vector_from_client(
			fcppt::math::vector::structure_cast<
				draw2d::vector2
			>(
				-
				fcppt::math::dim::structure_cast<
					sprite::point
				>(
					object_.screen_size() / 2u
				)
				+ object_.player_center().get()
				+ _cursor_position
			)
		);
}
