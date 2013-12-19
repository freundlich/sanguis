#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/container.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sanguis/gui/widget/reference_vector.hpp>
#include <sge/rucksack/aspect.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/widget/box/base.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::gui::widget::box_container::box_container(
	sanguis::gui::context &_context,
	sanguis::gui::widget::reference_alignment_vector const &_widgets,
	sge::rucksack::axis const _axis,
	sge::rucksack::aspect const _aspect
)
:
	sanguis::gui::widget::container(
		_context,
		fcppt::algorithm::map<
			sanguis::gui::widget::reference_vector
		>(
			_widgets,
			[](
				sanguis::gui::widget::reference_alignment_pair const &_pair
			)
			{
				return
					_pair.reference();
			}
		),
		// This is pretty dangerous but the base class only uses the
		// reference here
		layout_
	),
	layout_(
		_axis,
		_aspect
	)
{
	for(
		auto const &element
		:
		_widgets
	)
		layout_.push_back_child(
			element.reference().get().layout(),
			element.alignment()
		);
}

sanguis::gui::widget::box_container::~box_container()
{
}

void
sanguis::gui::widget::box_container::push_back(
	sanguis::gui::widget::reference_alignment_pair const &_pair
)
{
	this->push_back_widget(
		_pair.reference().get()
	);

	layout_.push_back_child(
		_pair.reference().get().layout(),
		_pair.alignment()
	);
}

void
sanguis::gui::widget::box_container::pop_back()
{
	this->pop_back_widget();

	// TODO: Do we have to pop back the layout as well?
}

sge::rucksack::widget::box::base &
sanguis::gui::widget::box_container::box_layout()
{
	return
		layout_;
}