#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/destructible_pos.hpp>
#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/parameters.hpp>
#include <sanguis/creator/impl/parameters_fwd.hpp>
#include <sanguis/creator/impl/result.hpp>
#include <sanguis/creator/impl/generators/start.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <sanguis/creator/impl/random/uniform_int.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/enum_array_fold.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/container/grid/make_pos_range_start_end.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/random/distribution/basic.hpp>


sanguis::creator::impl::result
sanguis::creator::impl::generators::start(
	sanguis::creator::impl::parameters const &_parameters
)
{
	sanguis::creator::dim const grid_size{
		10,
		10
	};

	sanguis::creator::grid grid{
		grid_size,
		sanguis::creator::tile::concrete_wall
	};

	for(
		auto const pos
		:
		fcppt::container::grid::make_pos_range_start_end(
			grid,
			sanguis::creator::pos(
				1,
				1
			),
			sanguis::creator::pos(
				grid_size.w() - 1u,
				grid_size.h() - 1u
			)
		)
	)
		pos.value() =
			sanguis::creator::tile::nothing;

	sanguis::creator::opening const start_portal{
		sanguis::creator::pos{
			1,
			grid_size.h()
			/
			2
		}
	};

	sanguis::creator::opening const exit_portal{
		sanguis::creator::pos{
			grid_size.w()
			-
			2,
			grid_size.h()
			/
			2
		}
	};

	sanguis::creator::background_grid bg_grid{
		grid_size,
		sanguis::creator::background_tile::dirt
	};

	typedef
	fcppt::random::distribution::basic<
		sanguis::creator::impl::random::uniform_int<
			unsigned
		>
	>
	uniform_int2;

	auto random_dirt_grass(
		fcppt::random::make_variate(
			_parameters.randgen(),
			uniform_int2{
				uniform_int2::param_type::min{
					0u
				},
				uniform_int2::param_type::max{
					1u
				}
			}
		)
	);

	for(
		auto const pos
		:
		fcppt::container::grid::make_pos_range_start_end(
			bg_grid,
			sanguis::creator::pos(
				1,
				1
			),
			sanguis::creator::pos(
				grid_size.w() - 1u,
				grid_size.h() - 1u
			)
		)
	)
		pos.value() =
			random_dirt_grass()
			?
			sanguis::creator::background_tile::dirt
			:
			sanguis::creator::background_tile::grass;

	grid[
		exit_portal.get()
	] =
		sanguis::creator::tile::stairs;

	return
		sanguis::creator::impl::result{
			grid,
			bg_grid,
			fcppt::algorithm::enum_array_fold<
				sanguis::creator::opening_container_array
			>(
				[
					start_portal,
					exit_portal
				](
					sanguis::creator::opening_type const _opening_type
				)
				{
					switch(
						_opening_type
					)
					{
					case sanguis::creator::opening_type::entry:
						return
							sanguis::creator::opening_container{
								start_portal
							};
					case sanguis::creator::opening_type::exit:
						return
							sanguis::creator::opening_container{
								exit_portal
							};
					}

					FCPPT_ASSERT_UNREACHABLE;
				}
			),
			sanguis::creator::spawn_container(),
			sanguis::creator::destructible_container{
				// TODO: Just for testing
				sanguis::creator::destructible(
					sanguis::creator::destructible_pos(
						sanguis::creator::pos(
							2,
							2
						)
					),
					sanguis::creator::destructible_type::barrel
				)
			}
		};
}