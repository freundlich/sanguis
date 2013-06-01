#include <sanguis/creator/car_park.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/parameters.hpp>
#include <sanguis/creator/result.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/tile.hpp>
#include <fcppt/text.hpp>

#include <sanguis/creator/randgen.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>


sanguis::creator::result
sanguis::creator::car_park(
	sanguis::creator::parameters const &_parameters
)
{
	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_real<
			double
		>
	> uniform_real;

	uniform_real distribution(
		uniform_real::param_type::min(
			0.0
		),
		uniform_real::param_type::sup(
			1.0
		)
	);

	sanguis::creator::grid ret(
		sanguis::creator::grid::dim(
			12, 12/*40,*/
			/*40*/
			/*
			_parameters.size().w(),
			_parameters.size().h()
			*/
		),
		sanguis::creator::tile::nothing
	);

	for (
		unsigned y = 0;
		y < ret.size().w();
		++y
	)
	{
		for (
			unsigned x = 0;
			x < ret.size().h();
			++x
		)
		{
			double const filled(
				distribution(
					_parameters.randgen()
				)
			);

			ret[
				sanguis::creator::grid::dim(
					x,
					y
				)
			] =
				filled < 0.15
				?
				sanguis::creator::tile::concrete_wall
				:
				sanguis::creator::tile::nothing;
		}
	}

	return
		sanguis::creator::result(
			ret,
			sanguis::creator::seed(
				0u
			),
			sanguis::creator::name(
				FCPPT_TEXT("car_park")
			)
		);
}
