#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/client/gui/perk/make_tabs.hpp>
#include <sanguis/client/gui/perk/tab.hpp>
#include <sanguis/client/gui/perk/tab_unique_ptr_vector.hpp>
#include <sanguis/client/perk/category_equal_range.hpp>
#include <sanguis/client/perk/state.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::perk::tab_unique_ptr_vector
sanguis::client::gui::perk::make_tabs(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::gui::context &_context,
	sanguis::client::perk::state &_state
)
{
	sanguis::client::perk::tree const &tree(
		_state.perks()
	);

	sanguis::client::gui::perk::tab_unique_ptr_vector result;

	for(
		sanguis::client::perk::const_tree_range range(
			sanguis::client::perk::category_equal_range(
				tree.begin(),
				tree.end()
			)
		);
		!range.empty();
		range =
			sanguis::client::perk::category_equal_range(
				range.end(),
				tree.end()
			)
	)
		result.push_back(
			fcppt::make_unique_ptr<
				sanguis::client::gui::perk::tab
			>(
				_renderer,
				_font,
				_context,
				_state,
				range
			)
		);

	return
		std::move(
			result
		);
}