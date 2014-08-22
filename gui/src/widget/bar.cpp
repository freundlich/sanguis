#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/fill_color.hpp>
#include <sanguis/gui/fill_level.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sanguis/gui/style/base.hpp>
#include <sanguis/gui/widget/bar.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/is_expanding.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/optional_scalar.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/widget/base.hpp>


sanguis::gui::widget::bar::bar(
	sanguis::gui::style::base const &_style,
	sge::rucksack::dim const _dim,
	sge::rucksack::axis const _axis,
	sanguis::gui::fill_color const &_foreground,
	sanguis::gui::fill_level const _value
)
:
	sanguis::gui::widget::base(),
	style_(
		_style
	),
	axis_{
		_axis
	},
	foreground_(
		_foreground
	),
	value_(
		_value
	),
	layout_(
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					_dim.w()
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()
				),
				sge::rucksack::is_expanding(
					_axis
					==
					sge::rucksack::axis::x
				)
			),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					_dim.h()
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()
				),
				sge::rucksack::is_expanding(
					_axis
					==
					sge::rucksack::axis::y
				)
			),
			sanguis::gui::default_aspect()
		)
	)
{
}

sanguis::gui::widget::bar::~bar()
{
}

void
sanguis::gui::widget::bar::value(
	sanguis::gui::fill_level const _value
)
{
	value_ =
		_value;
}

void
sanguis::gui::widget::bar::on_draw(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_render_context
)
{
	style_.draw_bar(
		_renderer,
		_render_context,
		this->layout().area(),
		axis_,
		value_,
		foreground_
	);
}

sge::rucksack::widget::base &
sanguis::gui::widget::bar::layout()
{
	return
		layout_;
}
