#include <sanguis/gui/context.hpp>
#include <sanguis/gui/draw.hpp>
#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/master.hpp>
#include <sanguis/gui/aux_/renderer/scoped.hpp>
#include <sanguis/gui/main_area/base.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/optional_focus.hpp>
#include <sanguis/gui/widget/optional_ref.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::gui::master::master(
	sge::input::keyboard::device &_keyboard,
	sge::input::cursor::object &_cursor,
	sanguis::gui::context &_context,
	sanguis::gui::main_area::base &_main_area
)
:
	cursor_(
		_cursor
	),
	context_(
		_context
	),
	main_area_(
		_main_area
	),
	key_connection_(
		_keyboard.key_callback(
			std::bind(
				&sanguis::gui::master::key_event,
				this,
				std::placeholders::_1
			)
		)
	),
	key_repeat_connection_(
		_keyboard.key_repeat_callback(
			std::bind(
				&sanguis::gui::master::key_repeat_event,
				this,
				std::placeholders::_1
			)
		)
	),
	char_connection_(
		_keyboard.char_callback(
			std::bind(
				&sanguis::gui::master::char_event,
				this,
				std::placeholders::_1
			)
		)
	),
	button_connection_(
		_cursor.button_callback(
			std::bind(
				&sanguis::gui::master::button_event,
				this,
				std::placeholders::_1
			)
		)
	)
{
}

sanguis::gui::master::~master()
{
}

void
sanguis::gui::master::draw(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sanguis::gui::background::base &_background
)
{
	sanguis::gui::draw(
		_renderer,
		_context,
		_background,
		main_area_
	);
}

void
sanguis::gui::master::draw_with_states(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sanguis::gui::background::base &_background
)
{
	sanguis::gui::aux_::renderer::scoped renderer(
		_renderer,
		_context
	);

	sanguis::gui::draw(
		renderer,
		_context,
		_background,
		main_area_
	);
}

void
sanguis::gui::master::update(
	sanguis::gui::duration const _duration
)
{
	this->widget().on_update(
		_duration
	);
}

void
sanguis::gui::master::key_event(
	sge::input::keyboard::key_event const &_event
)
{
	if(
		_event.pressed()
	)
		this->handle_key(
			_event.key_code()
		);
}

void
sanguis::gui::master::key_repeat_event(
	sge::input::keyboard::key_repeat_event const &_event
)
{
	this->handle_key(
		_event.key_code()
	);
}

void
sanguis::gui::master::char_event(
	sge::input::keyboard::char_event const &_event
)
{
	if(
		context_.focus()
	)
		context_.focus()->on_char(
			_event.character()
		);
}

void
sanguis::gui::master::button_event(
	sge::input::cursor::button_event const &_event
)
{
	sge::input::cursor::optional_position const pos(
		cursor_.position()
	);

	if(
		pos
		&&
		_event.pressed()
		&&
		_event.button_code()
		==
		sge::input::cursor::button_code::left
	)
		this->widget().on_click(
			fcppt::math::vector::structure_cast<
				sge::rucksack::vector
			>(
				*pos
			)
		);
}

void
sanguis::gui::master::handle_key(
	sge::input::keyboard::key_code const _key_code
)
{
	if(
		_key_code
		==
		sge::input::keyboard::key_code::tab
	)
	{
		// If no focus was found, try one more time using no focus
		// because the search can wrap around.
		if(
			!this->try_focus(
				sanguis::gui::widget::optional_focus(
					context_.focus()
				)
			)
		)
			this->try_focus(
				sanguis::gui::widget::optional_focus(
					sanguis::gui::widget::optional_ref()
				)
			);

		return;
	}

	if(
		context_.focus()
	)
		context_.focus()->on_key(
			_key_code
		);
}

sanguis::gui::widget::optional_ref const
sanguis::gui::master::try_focus(
	sanguis::gui::widget::optional_focus _focus
)
{
	sanguis::gui::widget::optional_ref const result(
		this->widget().on_tab(
			_focus
		)
	);

	if(
		result
	)
		context_.focus(
			*result
		);

	return
		result;
}

sanguis::gui::widget::base &
sanguis::gui::master::widget()
{
	return
		main_area_.widget();
}
