#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_DIM_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_DIM_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/type_choices.hpp>
#include <sge/sprite/types/dim.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

typedef sge::sprite::types::dim<
	sprite::type_choices
>::type dim;

}
}
}
}

#endif