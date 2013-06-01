#include <sanguis/creator/aux/neumann_neighbors.hpp>
#include <sanguis/creator/grid.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


// returns the points in the von-Neumann-neighborhood
// of the given cell,
// no range checks are being performed!
std::vector<
	sanguis::creator::grid::dim
>
sanguis::creator::aux::neumann_neighbors(
	sanguis::creator::grid::dim const &cell
)
{
	std::vector<sanguis::creator::grid::dim> ret{
			sanguis::creator::grid::dim{
				cell.w() - 1,
				cell.h()
			},
			sanguis::creator::grid::dim{
				cell.w() + 1,
				cell.h()
			},
			sanguis::creator::grid::dim{
				cell.w(),
				cell.h() - 1,
			},
			sanguis::creator::grid::dim{
				cell.w(),
				cell.h() + 1
			}
		};

	return ret;
}
