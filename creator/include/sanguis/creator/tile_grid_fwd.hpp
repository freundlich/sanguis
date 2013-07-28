#ifndef SANGUIS_CREATOR_TILE_GRID_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_TILE_GRID_FWD_HPP_INCLUDED

#include <fcppt/container/grid/object_fwd.hpp>


namespace sanguis
{
namespace creator
{

template<
	typename Tile
>
using
tile_grid
=
fcppt::container::grid::object<
	Tile,
	2u
>;

}
}

#endif
