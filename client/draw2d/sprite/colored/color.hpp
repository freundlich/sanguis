#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_COLOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_COLOR_HPP_INCLUDED

#include "color_format.hpp"
#include <sge/image/color/object.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace colored
{

typedef sge::image::color::object<
	color_format
>::type color;

}
}
}
}
}

#endif