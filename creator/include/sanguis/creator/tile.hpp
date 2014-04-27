#ifndef SANGUIS_CREATOR_TILE_HPP_INCLUDED
#define SANGUIS_CREATOR_TILE_HPP_INCLUDED

#include <sanguis/creator/tile_fwd.hpp>


namespace sanguis
{
namespace creator
{

enum class tile
{
	nothing,
	door,
	spawner,
	grave1,
	grave2,
	grave3,
	grave4,
	grave5,
	hedge,
	concrete_wall,
	fcppt_maximum = concrete_wall
};

}
}

#endif