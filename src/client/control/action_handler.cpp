#include "action_handler.hpp"
#include "action_visitor.hpp"
#include "axis_direction_max.hpp"
#include "axis_direction_min.hpp"
#include "environment.hpp"
#include "actions/any.hpp"
#include "actions/binary.hpp"
#include "actions/cursor.hpp"
#include "actions/nullary.hpp"
#include "actions/scale.hpp"
#include "../../messages/create.hpp"
#include "../../messages/player_attack_dest.hpp"
#include "../../messages/player_direction.hpp"
#include "../../messages/player_start_shooting.hpp"
#include "../../messages/player_stop_shooting.hpp"
#include "../../messages/player_change_weapon.hpp"
#include "../../messages/player_cheat.hpp"
#include "../../exception.hpp"
#include <sge/time/millisecond.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/console/object.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/cyclic_iterator.hpp>
#include <fcppt/text.hpp>
#include <algorithm>
#include <iterator>

sanguis::client::control::action_handler::action_handler(
	client::send_callback const &_send,
	control::environment &_environment,
	sge::console::object &_console
)
:
	send_(
		_send
	),
	environment_(
		_environment
	),
	current_weapon_(
		weapon_type::size
	),
	rotation_timer_(
		sge::time::millisecond(
			100
		)
	),
	owned_weapons_(),
	direction_(
		control::direction_vector::null()
	),
	cheat_kill_conn_(
		_console.insert(
			SGE_FONT_TEXT_LIT("kill"),
			std::tr1::bind(
				&action_handler::send_cheat,
				this,
				cheat_type::kill,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			SGE_FONT_TEXT_LIT("Commit suicide")
		)
	),
	cheat_impulse_conn_(
		_console.insert(
			SGE_FONT_TEXT_LIT("impulse"),
			std::tr1::bind(
				&action_handler::send_cheat,
				this,
				cheat_type::impulse101,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			SGE_FONT_TEXT_LIT("Get all weapons")
		)
	),
	cheat_exp_conn_(
		_console.insert(
			SGE_FONT_TEXT_LIT("exp"),
			std::tr1::bind(
				&action_handler::send_cheat,
				this,
				cheat_type::exp,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			SGE_FONT_TEXT_LIT("Get a lot of exp")
		)
	)
{
	std::fill(
		owned_weapons_.begin(),
		owned_weapons_.end(),
		false
	);
}

sanguis::client::control::action_handler::~action_handler()
{
}

void
sanguis::client::control::action_handler::handle_action(
	control::actions::any const &_action
)
{
	fcppt::variant::apply_unary(
		control::action_visitor(
			*this
		),
		_action.get()
	);
}

void
sanguis::client::control::action_handler::give_player_weapon(
	weapon_type::type const _weapon_type
)
{
	owned_weapons_.at(
		_weapon_type
	) = true;

	// we don't own any weapon so take this one
	if(
		current_weapon_ == weapon_type::size
	)
		this->change_weapon(
			_weapon_type
		);
}

void
sanguis::client::control::action_handler::handle_binary_action(
	control::actions::binary const &_action
)
{
	switch(
		_action.type()
	)
	{
	case actions::binary_type::shoot:
		this->handle_shooting(
			_action.value()
		);
		return;
	}


	throw sanguis::exception(
		FCPPT_TEXT("Invalid binary_action in action_handler!")
	);
}

void
sanguis::client::control::action_handler::handle_cursor_action(
	control::actions::cursor const &_action
)
{
	if(
		!rotation_timer_.update_b()
	)
		return;
	
	send_(
		sanguis::messages::create(
			sanguis::messages::player_attack_dest(
				fcppt::math::vector::structure_cast<
					sanguis::messages::types::vector2
				>(
					environment_.translate_attack_dest(
						_action.position()
					)
				)
			)
		)
	);
}

void
sanguis::client::control::action_handler::handle_nullary_action(
	control::actions::nullary const &_action
)
{
	switch(
		_action.type()
	)
	{
	case actions::nullary_type::switch_weapon_forwards:
		this->handle_switch_weapon(
			true
		);

		return;
	case actions::nullary_type::switch_weapon_backwards:
		this->handle_switch_weapon(
			false
		);

		return;
	// There are some actions we don't handle
	case actions::nullary_type::perk_menu:
	case actions::nullary_type::escape:
	case actions::nullary_type::console:
		break;
	}
}

void
sanguis::client::control::action_handler::handle_scale_action(
	control::actions::scale const &_action
)
{
	control::key_scale const scale(
		_action.get()
	);

	switch(
		_action.type()
	)
	{
	case actions::scale_type::horizontal_move:
		this->update_direction(
			direction_.x(),
			scale
		);

		return;
	case actions::scale_type::vertical_move:
		this->update_direction(
			direction_.y(),
			scale
		);

		return;
	}

	throw sanguis::exception(
		FCPPT_TEXT("Invalid scale_action in action_handler!")
	);
}

void
sanguis::client::control::action_handler::update_direction(
	control::scalar &_result,
	control::key_scale const _scale
)
{
	_result =
		fcppt::math::clamp(
			_result + _scale,
			control::axis_direction_min(),
			control::axis_direction_max()
		);

	send_(
		sanguis::messages::create(
			sanguis::messages::player_direction(
				fcppt::math::vector::structure_cast<
					sanguis::messages::types::vector2
				>(
					direction_
				)
			)
		)
	);
}

void
sanguis::client::control::action_handler::handle_shooting(
	bool const _value
)
{
	if(
		_value
	)
		send_(
			sanguis::messages::create(
				sanguis::messages::player_start_shooting()
			)
		);
	else
		send_(
			sanguis::messages::create(
				sanguis::messages::player_stop_shooting()
			)
		);
}

void
sanguis::client::control::action_handler::handle_switch_weapon(
	bool const _forward
)
{
	// we don't own any weapon
	if(
		current_weapon_ == weapon_type::size
	)
		return;

	owned_weapons_array::size_type const weapon_index(
		static_cast<
			owned_weapons_array::size_type
		>(
			current_weapon_
		)
	);

	FCPPT_ASSERT(
		weapon_index < owned_weapons_.size()
	);

	typedef fcppt::cyclic_iterator<
		owned_weapons_array::const_iterator
	> iterator;
	
	iterator it(
		owned_weapons_.begin()
		+ static_cast<
			owned_weapons_array::size_type
		>(
			current_weapon_
		),
		owned_weapons_.begin(),
		owned_weapons_.end()
	);

	if(
		_forward
	)
		while(!*++it) ;
	else
		while(!*--it) ;

	this->change_weapon(
		static_cast<
			weapon_type::type
		>(
			std::distance(
				static_cast<
					owned_weapons_array const &
				>(
					owned_weapons_
				).begin(),
				it.get()
			)
		)
	);
}

void
sanguis::client::control::action_handler::change_weapon(
	weapon_type::type const _weapon_type
)
{
	current_weapon_ = _weapon_type;

	send_(
		sanguis::messages::create(
			sanguis::messages::player_change_weapon(
				current_weapon_
			)
		)
	);
}

void
sanguis::client::control::action_handler::send_cheat(
	cheat_type::type const _cheat,
	sge::console::arg_list const &,
	sge::console::object &
)
{
	send_(
		sanguis::messages::create(
			sanguis::messages::player_cheat(
				_cheat
			)
		)
	);
}
