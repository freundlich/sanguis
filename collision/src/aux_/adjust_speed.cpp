#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/aux_/adjust_speed.hpp>
#include <sanguis/collision/aux_/is_null.hpp>
#include <sanguis/collision/aux_/line_segment.hpp>
#include <sanguis/collision/aux_/optional_intersection.hpp>
#include <sanguis/collision/aux_/rect.hpp>
#include <sanguis/collision/aux_/rect_line_intersection.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/box/expand.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/to_vector.hpp>


sanguis::collision::speed const
sanguis::collision::aux_::adjust_speed(
	sanguis::collision::aux_::line_segment const _movement,
	sanguis::collision::dim2 const _entity_size,
	sanguis::collision::aux_::rect const _obstacle,
	sanguis::collision::speed const _old_speed
)
{
	sanguis::collision::aux_::optional_intersection const intersection(
		sanguis::collision::aux_::rect_line_intersection(
			fcppt::math::box::expand(
				_obstacle,
				fcppt::math::dim::to_vector(
					_entity_size
					/
					fcppt::literal<
						sanguis::collision::unit
					>(
						2
					)
				)
			),
			_movement
		)
	);

	if(
		!intersection
	)
		return
			_old_speed;

	bool const vertical(
		sanguis::collision::aux_::is_null(
			intersection->dir().get().x()
		)
	);

	bool const horizontal(
		sanguis::collision::aux_::is_null(
			intersection->dir().get().y()
		)
	);

	FCPPT_ASSERT_ERROR(
		vertical
		!=
		horizontal
	);

	sanguis::collision::unit const zero(
		fcppt::literal<
			sanguis::collision::unit
		>(
			0
		)
	);

	return
		vertical
		?
			sanguis::collision::speed(
				sanguis::collision::vector2(
					zero,
					_old_speed.get().y()
				)
			)
		:
			sanguis::collision::speed(
				sanguis::collision::vector2(
					_old_speed.get().x(),
					zero
				)
			)
		;
}
