#ifndef SANGUIS_GUI_CREATE_TEXTURE_HPP_INCLUDED
#define SANGUIS_GUI_CREATE_TEXTURE_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>


namespace sanguis
{
namespace gui
{

SANGUIS_GUI_SYMBOL
sge::renderer::texture::planar_unique_ptr
create_texture(
	sge::renderer::device::core &,
	sge::image2d::view::const_object const &
);

}
}

#endif
