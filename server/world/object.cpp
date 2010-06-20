#include "object.hpp"
#include "environment.hpp"
#include "sight_range.hpp"
#include "context.hpp"
#include "prop.hpp"
#include "../collision/execute.hpp"
#include "../collision/execute_begin.hpp"
#include "../collision/execute_end.hpp"
#include "../collision/test.hpp"
#include "../collision/satellite.hpp"
#include "../entities/base.hpp"
#include "../entities/movable.hpp"
#include "../entities/with_health.hpp"
#include "../entities/with_dim.hpp"
#include "../entities/player.hpp"
#include "../message_convert/speed.hpp"
#include "../message_convert/rotate.hpp"
#include "../message_convert/move.hpp"
#include "../message_convert/health.hpp"
#include "../../messages/create.hpp"
#include "../../messages/remove.hpp"
#include "../../messages/die.hpp"
#include "../../messages/change_weapon.hpp"
#include "../../messages/experience.hpp"
#include "../../messages/give_weapon.hpp"
#include "../../messages/level_up.hpp"
#include "../../messages/start_attacking.hpp"
#include "../../messages/stop_attacking.hpp"
#include "../../messages/start_reloading.hpp"
#include "../../messages/stop_reloading.hpp"
#include "../../messages/max_health.hpp"
#include "../../load/model/context.hpp"
#include "../../load/model/collection.hpp"
#include "../../load/model/object.hpp"
#include "../../exception.hpp"
#include <sge/collision/system.hpp>
#include <sge/collision/world.hpp>
#include <sge/collision/box.hpp>
#include <sge/time/second.hpp>
#include <sge/time/millisecond.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/make_shared_ptr.hpp>
//#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

sanguis::server::world::object::object(
	context_ptr const global_context_,
	sge::collision::system_ptr const sys,
	server::environment::load_context_ptr const load_context_,
	server::console &console_
)
:
	global_context_(
		global_context_
	),
	load_context_(
		load_context_
	),
	collision_world_(
		sys->create_world(
			sge::collision::optional_box(
				sge::collision::box(
					// FIXME
					sge::collision::box::vector(
						-1000,
						-1000,
						0
					),
					sge::collision::box::dim(
						1000,
						1000,
						0	
					)
				)
			),
			sge::collision::constraint::constrain_2d
		)
	),
	collision_groups_(
		collision_world_
	),
	sight_ranges_(),
	diff_clock_(),
	send_timer_(
		sge::time::millisecond(
			500
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	),
	entities_(),
	props_(),
	collision_connection_begin_(
		collision_world_->register_begin_callback(
			std::tr1::bind(
				collision::execute,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				collision::execute_begin()
			)
		)
	),
	collision_connection_end_(
		collision_world_->register_end_callback(
			std::tr1::bind(
				collision::execute,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				collision::execute_end()
			)
		)
	),
	collision_connection_test_(
		collision_world_->register_test_callback(
			std::tr1::bind(
				collision::test,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		)
	),
	environment_(
		fcppt::make_shared_ptr<
			world::environment
		>(
			std::tr1::ref(
				*this
			)
		)
	),
	pickup_spawner_(
		environment_
	),
	wave_gen_(
		console_
	)
{}

sanguis::server::world::object::~object()
{}

void
sanguis::server::world::object::update(
	time_type const time_
)
{
	diff_clock_.update(
		time_
	);

	wave_gen_.process(
		time_,
		environment(),
		load_context_
	);

	// should we send position updates?
	bool const update_pos = send_timer_.update_b();

	collision_world_->update(
		static_cast<sge::time::funit>(	
			time_
		)
	);

	for (
		entity_map::iterator it(
			entities_.begin()
		),
		next(
			it
		);
		it != entities_.end();
		it = next
	)
	{
		++next;

		update_entity(
			it,
			time_,
			update_pos
		);
	}
}

void
sanguis::server::world::object::insert(
	entities::auto_ptr entity_,
	entities::insert_parameters const &insert_parameters_
)
{
	entity_id const id(
		entity_->id()
	);

	entity_->transfer(
		environment_,
		collision_groups_,
		insert_parameters_
	);

	typedef std::pair<
		entity_map::iterator,
		bool
	> return_type;
	
	return_type const ret(
		entities_.insert(
			id,
			entity_	
		)
	);

	if(
		!ret.second
	)
		throw exception(
			FCPPT_TEXT("Double insert of entity!")
		);
}

sanguis::server::environment::object_ptr const
sanguis::server::world::object::environment() const
{
	return environment_;
}

void
sanguis::server::world::object::weapon_changed(
	entity_id const id,
	weapon_type::type const wt
)
{
	send_entity_specific(
		id,
		messages::create(
			messages::change_weapon(
				id,
				wt
			)
		)
	);
}

void
sanguis::server::world::object::got_weapon(
	player_id const player_id_,
	entity_id const entity_id_,
	weapon_type::type const wt_
)
{
	send_player_specific(
		player_id_,
		messages::create(
			messages::give_weapon(
				entity_id_,
				wt_
			)
		)
	);
}

void
sanguis::server::world::object::attacking_changed(
	entity_id const id,
	bool const is_attacking
)
{
	send_entity_specific(
		id,
		is_attacking
		?
			messages::create(
				messages::start_attacking(
					id
				)
			)
		:
			messages::create(
				messages::stop_attacking(
					id
				)
			)
	);
}

void
sanguis::server::world::object::reloading_changed(
	entity_id const id,
	bool const is_reloading
)
{
	send_entity_specific(
		id,
		is_reloading
		?
			messages::create(
				messages::start_reloading(
					id
				)
			)
		:
			messages::create(
				messages::stop_reloading(
					id
				)
			)
	);
}

void
sanguis::server::world::object::max_health_changed(
	entity_id const id,
	health_type const health_
)
{
	send_entity_specific(
		id,
		messages::create(
			messages::max_health(
				id,
				health_
			)
		)
	);
}

void
sanguis::server::world::object::exp_changed(
	player_id const player_id_,
	entity_id const entity_id_,
	exp_type const exp_
)
{
	send_player_specific(
		player_id_,
		messages::create(
			messages::experience(
				entity_id_,
				exp_
			)
		)
	);
}

void
sanguis::server::world::object::level_changed(
	player_id const player_id_,
	entity_id const entity_id_,
	level_type const level_
)
{
	send_player_specific(
		player_id_,
		messages::create(
			messages::level_up(
				entity_id_,
				level_
			)
		)
	);
}

void
sanguis::server::world::object::pickup_chance(
	probability_type const spawn_chance_,
	pos_type const &center_
)
{
	pickup_spawner_.spawn(
		spawn_chance_,
		center_
	);
}

void
sanguis::server::world::object::request_transfer(
	world_id const world_id_,
	entity_id const entity_id_,
	entities::insert_parameters const &insert_parameters_
)
{
	entity_map::iterator const it(
		entities_.find(
			entity_id_
		)
	);

	if (
		it == entities_.end()
	)
		throw exception(
			FCPPT_TEXT("entity can't be transferred!")
		);

	entities::auto_ptr entity_(
		entities_.release(
			it
		).release()
	);

	global_context_->transfer_entity(
		world_id_,
		entity_,
		insert_parameters_
	);
}

void
sanguis::server::world::object::add_sight_range(
	player_id const player_id_,
	entity_id const target_id_
)
{
	sight_ranges_[
		player_id_
	].add(
		target_id_
	);
	
	entity_map::iterator const it(
		entities_.find(
			target_id_
		)
	);

	if(
		it == entities_.end()
	)
		throw exception(
			FCPPT_TEXT("can't get entity for sight update!")
		);

	entities::base &entity_(
		*it->second
	);

	if(
		entity_.server_only()
	)
		return;
			
	send_player_specific(
		player_id_,
		it->second->add_message(
			player_id_
		)
	);
}

void
sanguis::server::world::object::remove_sight_range(
	player_id const player_id_,
	entity_id const target_id_
)
{
	{
		sight_range_map::iterator const sight_it(
			sight_ranges_.find(
				player_id_
			)
		);

		FCPPT_ASSERT(
			sight_it != sight_ranges_.end()
		);

		sight_it->second.remove(
			target_id_
		);

		// if the player sees nothing here
		// it must have been deleted / moved
		// because the player always sees himself

		if(
			sight_it->second.empty()
		)
			sight_ranges_.erase(
				sight_it
			);
	}
	
	// if an entity has been removed
	// we have to tell the client that it is dead instead
	
	entity_map::const_iterator const it(
		entities_.find(
			target_id_
		)
	);

	FCPPT_ASSERT(
		it != entities_.end()
	);

	send_player_specific(
		player_id_,
		it->second->dead()
		?
			messages::create(
				messages::die(
					target_id_
				)
			)
		:
			messages::create(
				messages::remove(
					target_id_
				)
			)
	);
}

void
sanguis::server::world::object::remove_player(
	player_id const player_id_
)
{
	global_context_->remove_player(
		player_id_
	);
}

sge::collision::world_ptr const
sanguis::server::world::object::collision_world() const
{
	return collision_world_;
}

sanguis::server::collision::global_groups const &
sanguis::server::world::object::global_collision_groups() const
{
	return collision_groups_;
}

sanguis::server::environment::load_context_ptr const
sanguis::server::world::object::load_context() const
{
	return load_context_;
}

void
sanguis::server::world::object::send_entity_specific(
	entity_id const id,
	messages::auto_ptr msg
)
{
	BOOST_FOREACH(
		sight_range_map::const_reference range,
		sight_ranges_
	)
		if(
			range.second.contains(
				id
			)
		)
			global_context_->send_to_player(
				range.first,
				msg
			);
}

void
sanguis::server::world::object::send_player_specific(
	player_id const player_id_,
	messages::auto_ptr msg
)
{
	global_context_->send_to_player(
		player_id_,
		msg
	);
}

void
sanguis::server::world::object::update_entity(
	entity_map::iterator const it,
	time_type const time_,
	bool const update_pos
)
{
	entities::base &e(
		*it->second
	);

	e.update(
		static_cast<
			time_type
		>(
			time_
		)
	);

	if(
		!e.processed()
	)
	{
		e.may_be_deleted();
		return;
	}
	else if(
		e.dead()
	)
	{
		update_entity_health(
			e
		);

		e.die();
		
		// process collision end before the destructor is called
		e.destroy();

		entities_.erase(
			it
		);

		return;
	}


	if(
		e.server_only()
		|| !update_pos
	)
		return;


	send_entity_specific(
		e.id(),
		message_convert::rotate(
			e
		)
	);

	FCPPT_TRY_DYNAMIC_CAST(
		entities::with_dim const *,
		with_dim_,
		&e
	)
		send_entity_specific(
			with_dim_->id(),
			message_convert::move(
				*with_dim_
			)
		);

	FCPPT_TRY_DYNAMIC_CAST(
		entities::movable const *,
		movable_,
		&e
	)
		send_entity_specific(
			movable_->id(),
			message_convert::speed(
				*movable_
			)
		);

	update_entity_health(
		e
	);
}

void
sanguis::server::world::object::update_entity_health(
	entities::base &entity_
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		entities::with_health const *,
		with_health_,
		&entity_
	)
		send_entity_specific(
			with_health_->id(),
			message_convert::health(
				*with_health_	
			)
		);
}
