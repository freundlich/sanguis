#include <sanguis/client/cursor_fwd.hpp>
#include <sanguis/client/draw_base_unique_ptr.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/draw2d/create.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw_base_unique_ptr
sanguis::client::draw2d::create(
	sanguis::client::load::context const &_load_context,
	sanguis::client::load::hud::context &_hud_context,
	sanguis::client::sound_manager &_sound_manager,
	sanguis::gui::style::base const &_gui_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::viewport::manager &_viewport_manager,
	sanguis::client::player_health_callback const &_player_health_callback,
	sanguis::client::cursor &_cursor
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::object
		>(
			_load_context,
			_hud_context,
			_sound_manager,
			_gui_style,
			_renderer,
			_font,
			_viewport_manager,
			_player_health_callback,
			_cursor
		);
}