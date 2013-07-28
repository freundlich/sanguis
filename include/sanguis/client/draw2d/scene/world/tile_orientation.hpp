#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_ORIENTATION_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/tile_is_same.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/load/tiles/direction.hpp>
#include <sanguis/load/tiles/orientation.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

template<
	typename Tile
>
sanguis::load::tiles::orientation const
tile_orientation(
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::creator::pos const &_pos
)
{
	sanguis::load::tiles::orientation orientation{
		sanguis::load::tiles::orientation::null()
	};

	Tile const tile(
		_grid[
			_pos
		]
	);

	orientation[
		sanguis::load::tiles::direction::north
	] =
		sanguis::client::draw2d::scene::world::tile_is_same(
			tile,
			_grid,
			sanguis::creator::pos(
				_pos.x(),
				_pos.y() - 1
			)
		);

	orientation[
		sanguis::load::tiles::direction::west
	] =
		sanguis::client::draw2d::scene::world::tile_is_same(
			tile,
			_grid,
			sanguis::creator::pos(
				_pos.x() - 1,
				_pos.y()
			)
		);

	orientation[
		sanguis::load::tiles::direction::east
	] =
		sanguis::client::draw2d::scene::world::tile_is_same(
			tile,
			_grid,
			sanguis::creator::pos(
				_pos.x() + 1,
				_pos.y()
			)
		);

	orientation[
		sanguis::load::tiles::direction::south
	] =
		sanguis::client::draw2d::scene::world::tile_is_same(
			tile,
			_grid,
			sanguis::creator::pos(
				_pos.x(),
				_pos.y() + 1
			)
		);

	return
		orientation;
}

}
}
}
}
}

#endif
