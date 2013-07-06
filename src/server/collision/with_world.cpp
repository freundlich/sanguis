#include <sanguis/duration.hpp>
#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/optional_result.hpp>
#include <sanguis/server/collision/result.hpp>
#include <sanguis/server/collision/with_world.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/speed.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <fcppt/optional_dynamic_cast.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sanguis::server::collision::optional_result const
sanguis::server::collision::with_world(
	sanguis::server::entities::base const &_base,
	sanguis::creator::grid const &_grid,
	sanguis::duration const &_duration
)
{
	typedef fcppt::optional<
		sanguis::server::entities::with_body const &
	> optional_with_body;

	optional_with_body const with_body(
		fcppt::optional_dynamic_cast<
			sanguis::server::entities::with_body const &
		>(
			_base
		)
	);

	if(
		!with_body
	)
		return
			sanguis::server::collision::optional_result();

	sanguis::server::space_unit const pixels_per_meter(
		static_cast<
			sanguis::server::space_unit
		>(
			sanguis::pixels_per_meter()
		)
	);

	sanguis::collision::optional_result const result(
		sanguis::collision::test_move(
			sanguis::collision::center(
				with_body->center().get()
				*
				pixels_per_meter
			),
			fcppt::math::dim::fill<
				sanguis::collision::dim2::dim_wrapper::value
			>(
				with_body->radius().get()
				*
				pixels_per_meter
			),
			sanguis::collision::speed(
				sanguis::server::entities::speed(
					*with_body
				).get()
				*
				pixels_per_meter
			),
			_duration,
			_grid
		)
	);

	return
		result
		?
			sanguis::server::collision::optional_result(
				sanguis::server::collision::result(
					sanguis::server::speed(
						result->speed().get()
						/
						pixels_per_meter
					),
					sanguis::server::center(
						result->center().get()
						/
						pixels_per_meter
					)
				)
			)
		:
			sanguis::server::collision::optional_result()
		;
}
