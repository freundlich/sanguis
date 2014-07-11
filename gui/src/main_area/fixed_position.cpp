#include <sanguis/gui/main_area/base.hpp>
#include <sanguis/gui/main_area/fixed_position.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/minimum_size.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>


sanguis::gui::main_area::fixed_position::fixed_position(
	sanguis::gui::widget::base &_widget,
	sge::rucksack::vector const _position
)
:
	sanguis::gui::main_area::base(),
	widget_(
		_widget
	),
	minimum_size_(
		widget_
	)
{
	minimum_size_.layout().position(
		_position
	);

	this->relayout();
}

sanguis::gui::main_area::fixed_position::~fixed_position()
{
}

void
sanguis::gui::main_area::fixed_position::relayout()
{
	minimum_size_.layout().relayout();
}

sanguis::gui::widget::base &
sanguis::gui::main_area::fixed_position::widget()
{
	return
		widget_;
}