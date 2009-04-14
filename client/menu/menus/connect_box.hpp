#ifndef SANGUIS_CLIENT_MENU_MENUS_CONNECT_BOX_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_MENUS_CONNECT_BOX_HPP_INCLUDED

#include <sge/systems/instance_fwd.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/widget.hpp>

namespace sanguis
{
namespace client
{
namespace menu
{
namespace menus
{
struct connect_box
{
	connect_box(
		sge::gui::widget::parent_data const &,
		sge::systems::instance const &);

	sge::gui::widget parent;
		sge::gui::widget label_wrapper;
			sge::gui::widgets::label label_;
		sge::gui::widget buttons;
			sge::gui::widgets::buttons::text buttons_retry;
			sge::gui::widgets::buttons::text buttons_cancel;
};
}
}
}
}

#endif // SANGUIS_CLIENT_MENU_MENUS_CONNECT_BOX_HPP_INCLUDED
