#include "connect_box.hpp"
#include "../../../resolution.hpp"
#include <sge/font/align_h.hpp>
#include <sge/font/align_v.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/structure_cast.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/text.hpp>

sanguis::client::menu::menus::connect_box::connect_box(
	sge::gui::widget::parent_data const &_parent)
:
	parent(
		_parent,
		sge::gui::widget::parameters()
			.pos(
				sge::gui::point::null())
			.size(
				sge::structure_cast<sge::gui::dim>(
					resolution()))
			.activation(
				sge::gui::activation_state::inactive)
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::vertical>())),

	label_(
		parent,
		sge::gui::widget::parameters(),
		SGE_TEXT("foobar"),
		sge::font::align_h::center,
		sge::font::align_v::center),
	
	buttons(
		parent,
		sge::gui::widget::parameters()
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::horizontal>())),
	
	buttons_retry(
		buttons,
		sge::gui::widget::parameters(),
		SGE_TEXT("Retry")),

	buttons_cancel(
		buttons,
		sge::gui::widget::parameters(),
		SGE_TEXT("Cancel"))
{
}
