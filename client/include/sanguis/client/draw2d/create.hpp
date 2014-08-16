#ifndef SANGUIS_CLIENT_DRAW2D_CREATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_CREATE_HPP_INCLUDED

#include <sanguis/client/cursor_fwd.hpp>
#include <sanguis/client/draw_base_unique_ptr.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{

sanguis::client::draw_base_unique_ptr
create(
	sanguis::client::load::context const &,
	sanguis::client::load::hud::context &,
	sanguis::client::sound_manager &,
	sanguis::gui::style::base const &,
	sge::renderer::device::ffp &,
	sge::font::object &,
	sge::viewport::manager &,
	sanguis::client::player_health_callback const &,
	sanguis::client::cursor &
);

}
}
}

#endif