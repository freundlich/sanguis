#ifndef SANGUIS_GUI_BACKGROUND_IMAGE_HPP_INCLUDED
#define SANGUIS_GUI_BACKGROUND_IMAGE_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/background/base.hpp>
#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace background
{

class image
:
	public sanguis::gui::background::base
{
	FCPPT_NONCOPYABLE(
		image
	);
public:
	SANGUIS_GUI_SYMBOL
	image(
		sge::renderer::device::ffp &,
		sanguis::gui::main_area::base &,
		sge::texture::const_part_shared_ptr
	);

	SANGUIS_GUI_SYMBOL
	~image()
	override;
private:
	void
	on_draw(
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	)
	override;

	sge::renderer::device::ffp &renderer_;

	sge::texture::const_part_shared_ptr const texture_;
};

}
}
}

#endif
