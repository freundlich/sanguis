#include <sanguis/client/gui/menu/resolution_chooser.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/index.hpp>
#include <sge/gui/optional_index.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/string_container.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/choices.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/display_mode/fullscreen.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/renderer/display_mode/output.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::gui::menu::resolution_chooser::resolution_chooser(
	sge::gui::context_ref const _context,
	sge::gui::style::const_reference const _style,
	sge::font::object_ref const _font,
	sge::renderer::device::ffp_ref const _renderer
)
:
	display_modes_(
		_renderer.get().display_modes()
	),
	renderer_(
		_renderer
	),
	choices_(
		_context,
		_style,
		_renderer,
		_font,
		// TODO: Add window mode
		fcppt::algorithm::map<
			sge::gui::string_container
		>(
			display_modes_,
			[](
				sge::renderer::display_mode::object const &_display_mode
			)
			{
				return
					sge::font::from_fcppt_string(
						fcppt::output_to_fcppt_string(
							_display_mode
						)
					);
			}
		),
		display_modes_.empty()
		?
			sge::gui::optional_index()
		:
			sge::gui::optional_index(
				// TODO
				sge::gui::index(
					0u
				)
			)
	),
	apply_button_(
		_style,
		_renderer,
		_font,
		SGE_FONT_LIT("Apply"),
		sge::gui::optional_needed_width()
	),
	widget_(
		_context,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference{
					choices_
				},
				sge::rucksack::alignment::center
			},
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference{
					apply_button_
				},
				sge::rucksack::alignment::center
			}
		},
		sge::rucksack::axis::y
	),
	apply_connection_{
		apply_button_.click(
			sge::gui::click_callback{
				std::bind(
					&sanguis::client::gui::menu::resolution_chooser::on_apply,
					this
				)
			}
		)
	}
{
}

FCPPT_PP_POP_WARNING

sanguis::client::gui::menu::resolution_chooser::~resolution_chooser()
{
}

sge::gui::widget::base &
sanguis::client::gui::menu::resolution_chooser::widget()
{
	return
		widget_;
}

void
sanguis::client::gui::menu::resolution_chooser::on_apply()
{
	fcppt::optional::maybe_void(
		choices_.index(),
		[
			this
		](
			sge::gui::index const _index
		)
		{
			renderer_.get().fullscreen(
				sge::renderer::display_mode::optional_fullscreen(
					sge::renderer::display_mode::fullscreen{
						display_modes_[
							_index.get()
						]
					}
				)
			);
		}
	);
}
