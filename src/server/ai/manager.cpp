#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/idle.hpp>
#include <sanguis/server/ai/manager.hpp>
#include <sanguis/server/ai/rotate_and_move_to_target.hpp>
#include <sanguis/server/ai/update_result.hpp>
#include <sanguis/server/ai/pathing/find_target.hpp>
#include <sanguis/server/ai/pathing/is_visible.hpp>
#include <sanguis/server/ai/pathing/positions_are_close.hpp>
#include <sanguis/server/ai/pathing/start.hpp>
#include <sanguis/server/ai/pathing/target.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <sanguis/server/auras/aggro.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::manager::manager(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::ai::base &_ai,
	sanguis::server::entities::with_ai &_me
)
:
	ai_(
		_ai
	),
	me_(
		_me
	),
	potential_targets_(),
	update_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			std::chrono::milliseconds(
				500
			)
		)
		.expired(
			true
		)
	),
	trail_()
{
	_me.add_aura(
		fcppt::make_unique_ptr<
			sanguis::server::auras::aggro
		>(
			// TODO: sight_range could dynamically change in the future
			sanguis::server::radius(
				ai_.sight_range().get()
			),
			_me.team(),
			std::bind(
				&sanguis::server::ai::manager::target_enters,
				this,
				std::placeholders::_1
			),
			std::bind(
				&sanguis::server::ai::manager::target_leaves,
				this,
				std::placeholders::_1
			)
		)
	);
}

sanguis::server::ai::manager::~manager()
{
}

void
sanguis::server::ai::manager::update()
{
	if(
		!sge::timer::reset_when_expired(
			update_timer_
		)
	)
		return;

	// TODO: How should we track this?
	for(
		auto ref : potential_targets_
	)
		this->update_target(
			ai_.distance_changes(
				ref.get()
			)
		);

	sanguis::server::entities::auto_weak_link const target(
		ai_.target()
	);

	if(
		!target
	)
	{
		sanguis::server::ai::idle(
			me_
		);

		return;
	}

	sanguis::creator::pos const target_grid_pos(
		sanguis::server::world::center_to_grid_pos(
			target->center()
		)
	);

	sanguis::creator::pos const my_grid_pos(
		sanguis::server::world::center_to_grid_pos(
			me_.center()
		)
	);

	me_.target(
		sanguis::server::weapons::target(
			target->center().get()
		)
	);

	sanguis::creator::grid const &grid(
		me_.environment().grid()
	);

	me_.use_weapon(
		sanguis::server::ai::pathing::is_visible(
			grid,
			target_grid_pos,
			my_grid_pos
		),
		sanguis::is_primary_weapon(
			true
		)
	);

	if(
		sanguis::server::ai::pathing::positions_are_close(
			target_grid_pos,
			my_grid_pos
		)
	)
	{
		sanguis::server::ai::rotate_and_move_to_target(
			me_,
			target->center()
		);

		return;
	}

	if(
		trail_.empty()
		||
		!sanguis::server::ai::pathing::positions_are_close(
			trail_.front(),
			target_grid_pos
		)
	)
		trail_ =
			sanguis::server::ai::pathing::find_target(
				grid,
				sanguis::server::ai::pathing::start(
					my_grid_pos
				),
				sanguis::server::ai::pathing::target(
					target_grid_pos
				)
			);

	if(
		trail_.empty()
	)
	{
		sanguis::server::ai::idle(
			me_
		);

		return;
	}

	sanguis::creator::pos const next_position(
		trail_.back()
	);

	sanguis::server::ai::rotate_and_move_to_target(
		me_,
		sanguis::server::world::grid_pos_to_center(
			next_position
		)
	);

	if(
		sanguis::server::ai::pathing::positions_are_close(
			my_grid_pos,
			next_position
		)
	)
		trail_.pop_back();
}

void
sanguis::server::ai::manager::target_enters(
	sanguis::server::entities::with_body &_with_body
)
{
	FCPPT_ASSERT_ERROR(
		potential_targets_.insert(
			fcppt::make_ref(
				_with_body
			)
		)
		.second
	);

	this->update_target(
		ai_.in_range(
			_with_body
		)
	);
}

void
sanguis::server::ai::manager::target_leaves(
	sanguis::server::entities::with_body &_with_body
)
{
	FCPPT_ASSERT_ERROR(
		potential_targets_.erase(
			fcppt::make_ref(
				_with_body
			)
		)
		==
		1u
	);

	this->update_target(
		ai_.out_of_range(
			_with_body
		)
	);
}

void
sanguis::server::ai::manager::update_target(
	sanguis::server::ai::update_result const _result
)
{
	if(
		_result
		==
		sanguis::server::ai::update_result::new_target
		||
		_result
		==
		sanguis::server::ai::update_result::lost_target
	)
		trail_.clear();

	// TODO: Search for a new target here!
	/*
	if(
		_result
		==
		sanguis::server::ai::update_result::lost_target
	)*/
}
