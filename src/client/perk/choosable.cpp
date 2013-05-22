#include <sanguis/perk_type.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/choosable.hpp>
#include <sanguis/client/perk/choosable_state.hpp>
#include <sanguis/client/perk/find_info.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/level.hpp>
#include <sanguis/client/perk/level_map.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/tree/object_impl.hpp>


namespace
{

sanguis::client::perk::level const
perk_level(
	sanguis::perk_type,
	sanguis::client::perk::level_map const &
);

}

sanguis::client::perk::choosable_state
sanguis::client::perk::choosable(
	sanguis::perk_type const _type,
	sanguis::client::perk::tree const &_tree,
	sanguis::client::perk::level_map const &_levels,
	sanguis::client::player_level const _player_level,
	sanguis::client::level const _perks_chosen
)
{
	sanguis::client::perk::tree const &node(
		sanguis::client::perk::find_info(
			_type,
			_tree
		)
	);

	FCPPT_ASSERT_PRE(
		node.value().has_value()
	);

	sanguis::client::perk::info const &info(
		*node.value()
	);

	FCPPT_ASSERT_PRE(
		node.has_parent()
	);

	if(
		info.max_level().get()
		==
		::perk_level(
			_type,
			_levels
		)
	)
		return sanguis::client::perk::choosable_state::max_level;

	if(
		node.parent().has_value()
		&&
		::perk_level(
			node.parent()->value()->type(),
			_levels
		)
		<
		info.required_parent_level().get()
	)
		return sanguis::client::perk::choosable_state::parent_level;

	if(
		info.required_player_level().get()
		>
		_player_level
	)
		return sanguis::client::perk::choosable_state::player_level;

	if(
		_player_level.get()
		==
		_perks_chosen
	)
		return sanguis::client::perk::choosable_state::level_up;

	return sanguis::client::perk::choosable_state::ok;
}

namespace
{

sanguis::client::perk::level const
perk_level(
	sanguis::perk_type const _type,
	sanguis::client::perk::level_map const &_map
)
{
	sanguis::client::perk::level_map::const_iterator const it(
		_map.find(
			_type
		)
	);

	return
		it == _map.end()
		?
			sanguis::client::perk::level(
				sanguis::client::level(
					0u
				)
			)
		:
			it->second;
}

}
