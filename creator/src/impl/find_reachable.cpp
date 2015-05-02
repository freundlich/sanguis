#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/impl/find_reachable.hpp>
#include <sanguis/creator/impl/reachable.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/container/grid/object.hpp>


sanguis::creator::impl::reachable_grid
sanguis::creator::impl::find_reachable(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const _start
)
{

	sanguis::creator::impl::reachable_grid
	result(
		sanguis::creator::impl::reachable_grid::dim(
			_grid.size()),
		sanguis::creator::impl::reachable(
			false)
	);

	std::vector<
		sanguis::creator::pos
	> queue;

	queue.push_back(
		_start);

	while(
		!queue.empty()
	)
	{
		sanguis::creator::pos
		pos =
			queue.back();

		queue.pop_back();

		result
		[
			pos
		] =
			true;

		for(
			auto const &n :
			fcppt::container::grid::neumann_neighbors(
				pos)
		)
			if(
					result
					[
						n
					]
					.get()
				==
					false
				&&
					!sanguis::creator::tile_is_solid(
						_grid
						[
							n
						]
					)
			)
				queue.push_back(n);
	}

	return result;
}