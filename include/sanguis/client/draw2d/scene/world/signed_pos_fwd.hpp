#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SIGNED_POS_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SIGNED_POS_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/signed_unit.hpp>
#include <fcppt/container/grid/dim_fwd.hpp>


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

typedef fcppt::container::grid::dim<
	sanguis::client::draw2d::scene::world::signed_unit,
	2
>::type signed_pos;

}
}
}
}
}

#endif
