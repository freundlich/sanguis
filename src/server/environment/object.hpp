#ifndef SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "load_context_ptr.hpp"
#include "../entities/unique_ptr.hpp"
#include "../entities/insert_parameters_fwd.hpp"
#include "../collision/global_groups_fwd.hpp"
#include "../player_id.hpp"
#include "../health_type.hpp"
#include "../exp_type.hpp"
#include "../level_type.hpp"
#include "../pos_type.hpp"
#include "../probability_type.hpp"
#include "../../world_id.hpp"
#include "../../weapon_type.hpp"
#include "../../entity_id.hpp"
#include <sge/collision/world_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace environment
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
protected:
	object();
public:
	virtual void 
	insert(
		entities::unique_ptr,
		entities::insert_parameters const &
	) = 0;

	virtual void
	weapon_changed(
		entity_id id,
		weapon_type::type
	) = 0;

	virtual void
	got_weapon(
		player_id,
		entity_id,
		weapon_type::type
	) = 0;

	virtual void
	attacking_changed(
		entity_id,
		bool is_attacking
	) = 0;

	virtual void
	reloading_changed(
		entity_id,
		bool is_reloading
	) = 0;

	virtual void
	max_health_changed(
		entity_id,
		server::health_type
	) = 0;

	virtual void
	exp_changed(
		player_id,
		entity_id,
		exp_type
	) = 0;

	virtual void
	level_changed(
		player_id,
		entity_id,
		level_type
	) = 0;

	virtual void
	pickup_chance(
		probability_type spawn_chance,
		pos_type const &center
	) = 0;

	virtual void
	request_transfer(
		world_id,
		entity_id,
		entities::insert_parameters const &
	) = 0;

	virtual void
	add_sight_range(
		player_id,
		entity_id
	) = 0;

	virtual void
	remove_sight_range(
		player_id,
		entity_id
	) = 0;

	virtual void
	remove_player(
		player_id
	) = 0;

	virtual sge::collision::world_ptr const
	collision_world() const = 0;

	virtual collision::global_groups const &
	global_collision_groups() const = 0;

	virtual load_context_ptr const
	load_context() const = 0;

	virtual ~object();
};

}
}
}

#endif