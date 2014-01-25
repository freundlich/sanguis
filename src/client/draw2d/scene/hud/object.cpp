#include <sanguis/duration.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type_to_is_primary.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/exp_for_next_level.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/max_health_valid.hpp>
#include <sanguis/client/draw2d/scene/hud/object.hpp>
#include <sanguis/client/draw2d/scene/hud/weapon_widget.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/widget/bar.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/vector.hpp>
#include <fcppt/insert_to_string.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::hud::object::object(
	sanguis::load::resource::textures const &_textures,
	sge::font::object &_font,
	sge::renderer::device::ffp &_renderer,
	sge::input::keyboard::device &_keyboard,
	sge::input::cursor::object &_cursor
)
:
	resources_(
		_textures
	),
	exp_(
		0u
	),
	previous_exp_level_(
		0u
	),
	exp_for_next_level_(
		0u
	),
	frames_counter_(),
	gui_context_(),
	player_name_text_(
		_renderer,
		_font,
		// TODO!
		SGE_FONT_LIT("Player")
	),
	level_text_(
		_renderer,
		_font,
		sge::font::string()
	),
	top_container_(
		gui_context_,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					player_name_text_
				),
				sge::rucksack::alignment::left_or_top
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					level_text_
				),
				sge::rucksack::alignment::right_or_bottom
			)
		},
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	),
	exp_bar_(
		_renderer,
		sge::rucksack::dim(
			200,
			10
		),
		sge::image::color::predef::forestgreen(),
		sanguis::gui::widget::bar::fill_level(
			0.f
		)
	),
	health_bar_(
		_renderer,
		sge::rucksack::dim(
			200,
			20
		),
		sge::image::color::predef::red(),
		sanguis::gui::widget::bar::fill_level(
			1.f
		)
	),
	primary_weapon_(
		resources_,
		gui_context_,
		_renderer,
		_font
	),
	secondary_weapon_(
		resources_,
		gui_context_,
		_renderer,
		_font
	),
	weapon_container_(
		gui_context_,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					primary_weapon_.widget()
				),
				sge::rucksack::alignment::left_or_top
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					secondary_weapon_.widget()
				),
				sge::rucksack::alignment::left_or_top
			)
		},
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	),
	main_widget_(
		gui_context_,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					top_container_
				),
				sge::rucksack::alignment::left_or_top
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					exp_bar_
				),
				sge::rucksack::alignment::left_or_top
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					health_bar_
				),
				sge::rucksack::alignment::left_or_top
			),
			sanguis::gui::widget::reference_alignment_pair(
				sanguis::gui::widget::reference(
					weapon_container_
				),
				sge::rucksack::alignment::left_or_top
			)
		},
		sge::rucksack::axis::y,
		sanguis::gui::default_aspect()
	),
	gui_master_(
		_renderer,
		_keyboard,
		_cursor,
		gui_context_,
		main_widget_
	),
	gui_area_(
		// TODO!
		sge::rucksack::rect(
			sge::rucksack::vector::null(),
			sge::rucksack::dim(
				250,
				300
			)
		),
		main_widget_.layout()
	)
{
}

sanguis::client::draw2d::scene::hud::object::~object()
{
}

void
sanguis::client::draw2d::scene::hud::object::health_pair(
	sanguis::client::health_pair const &_health_pair
)
{
	FCPPT_ASSERT_PRE(
		sanguis::client::max_health_valid(
			_health_pair.max_health()
		)
	);

	health_bar_.value(
		fcppt::strong_typedef_construct_cast<
			sanguis::gui::widget::bar::fill_level
		>(
			_health_pair.health().get()
		)
		/
		fcppt::strong_typedef_construct_cast<
			sanguis::gui::widget::bar::fill_level
		>(
			_health_pair.max_health().get()
		)
	);
}

void
sanguis::client::draw2d::scene::hud::object::experience(
	sanguis::client::exp const _exp
)
{
	exp_ =
		_exp;

	this->update_exp();
}

void
sanguis::client::draw2d::scene::hud::object::level(
	sanguis::client::level const _level,
	sanguis::client::exp_for_next_level const _exp_for_next_level
)
{
	level_text_.value(
		SGE_FONT_LIT("Level: ")
		+
		fcppt::insert_to_string<
			sge::font::string
		>(
			_level
		)
	);

	previous_exp_level_ =
		exp_for_next_level_;

	exp_for_next_level_ =
		_exp_for_next_level;

	this->update_exp();
}

void
sanguis::client::draw2d::scene::hud::object::add_weapon(
	sanguis::weapon_description const &_description
)
{
	this->weapon_widget(
		sanguis::weapon_type_to_is_primary(
			_description.weapon_type()
		)
	).weapon_description(
		sanguis::optional_weapon_description(
			_description
		)
	);
}

void
sanguis::client::draw2d::scene::hud::object::remove_weapon(
	sanguis::is_primary_weapon const _is_primary
)
{
	this->weapon_widget(
		_is_primary
	).weapon_description(
		sanguis::optional_weapon_description()
	);
}

void
sanguis::client::draw2d::scene::hud::object::update(
	sanguis::duration const &_duration
)
{
	gui_master_.update(
		// TODO: Put this into a function!
		std::chrono::duration_cast<
			sanguis::gui::duration
		>(
			_duration
		)
	);
}

void
sanguis::client::draw2d::scene::hud::object::draw(
	sge::renderer::context::ffp &_render_context
)
{
	frames_counter_.update();

	gui_master_.draw(
		_render_context
	);
}

sanguis::client::draw2d::scene::hud::weapon_widget &
sanguis::client::draw2d::scene::hud::object::weapon_widget(
	sanguis::is_primary_weapon const _is_primary
)
{
	return
		_is_primary.get()
		?
			primary_weapon_
		:
			secondary_weapon_
		;
}

void
sanguis::client::draw2d::scene::hud::object::update_exp()
{
	sanguis::client::exp_for_next_level const diff(
		exp_for_next_level_
		-
		previous_exp_level_
	);

	if(
		diff.get()
		==
		0u
	)
		return;

	exp_bar_.value(
		fcppt::strong_typedef_construct_cast<
			sanguis::gui::widget::bar::fill_level
		>(
			exp_.get()
			-
			previous_exp_level_.get()
		)
		/
		fcppt::strong_typedef_construct_cast<
			sanguis::gui::widget::bar::fill_level
		>(
			diff.get()
		)
	);
}