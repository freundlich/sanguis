#ifndef SANGUIS_GUI_WIDGET_IMAGE_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_IMAGE_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/image_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class image
:
	public sanguis::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		image
	);
public:
	SANGUIS_GUI_SYMBOL
	image(
		sanguis::gui::style::base const &,
		sge::texture::part const &
	);

	SANGUIS_GUI_SYMBOL
	~image()
	override;

	SANGUIS_GUI_SYMBOL
	sge::rucksack::widget::base &
	layout()
	override;
private:
	void
	on_draw(
		sanguis::gui::renderer::base &,
		sge::renderer::context::ffp &
	)
	override;

	sanguis::gui::style::base const &style_;

	sge::texture::part const &texture_;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif
