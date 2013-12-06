#ifndef SANGUIS_GUI_WIDGET_EDIT_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_EDIT_HPP_INCLUDED

#include <sanguis/gui/text_callback.hpp>
#include <sanguis/gui/text_function.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/edit_fwd.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/input/keyboard/key_code_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class edit
:
	public sanguis::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		edit
	);
public:
	edit(
		sanguis::gui::widget::base &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::font::string const &
	);

	~edit();

	sge::font::string const &
	text() const;

	fcppt::signal::auto_connection
	text_change(
		sanguis::gui::text_callback const &
	);
private:
	void
	on_update()
	override;

	void
	on_draw(
		sge::renderer::context::ffp &
	)
	override;

	void
	on_key(
		sge::input::keyboard::key_code
	)
	override;

	void
	on_char(
		sge::font::char_type
	);

	sge::rucksack::widget::base &
	layout()
	override;

	void
	text_change();

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sge::font::string text_;

	sge::font::string::size_type position_;

	sge::rucksack::widget::dummy layout_;

	typedef
	fcppt::signal::object<
		sanguis::gui::text_function
	>
	text_signal;

	text_signal text_change_;
};

}
}
}

#endif
