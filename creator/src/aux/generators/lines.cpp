#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/signed_pos_fwd.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux/bresenham.hpp>
#include <sanguis/creator/aux/parameters.hpp>
#include <sanguis/creator/aux/randgen.hpp>
#include <sanguis/creator/aux/result.hpp>
#include <sanguis/creator/aux/generators/lines.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

sanguis::creator::aux::result
sanguis::creator::aux::generators::lines(
	sanguis::creator::aux::parameters const &_parameters
)
{
	sanguis::creator::grid ret(
		sanguis::creator::grid::dim(
			31u,
			31u
		),
		sanguis::creator::tile::nothing
	);

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::creator::size_type
		>
	> uniform_int;

	uniform_int w_dist(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
			ret.size().w() - 1
		)
	);

	uniform_int h_dist(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
			ret.size().h() - 1
		)
	);

	for (unsigned i = 0; i < 5; ++i)
		sanguis::creator::aux::bresenham(
			sanguis::creator::signed_pos(
				w_dist(_parameters.randgen()),
				h_dist(_parameters.randgen())),
			sanguis::creator::signed_pos(
				w_dist(_parameters.randgen()),
				h_dist(_parameters.randgen())),
			[&ret](
				sanguis::creator::signed_pos pos
			)
			{
				auto p =
					fcppt::math::vector::structure_cast<
						sanguis::creator::pos
					>(
						pos);

				if (fcppt::container::grid::in_range(ret, p))
				ret[p] = sanguis::creator::tile::concrete_wall;
			}
		);

	// FIXME
	sanguis::creator::opening_container openings
	{
		sanguis::creator::opening(
			sanguis::creator::pos(
				0,
				0)),
		sanguis::creator::opening(
			sanguis::creator::pos(
				0,
				1)),
	};

	return
		sanguis::creator::aux::result(
			ret,
			openings
		);
}