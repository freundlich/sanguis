#ifndef SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED

#include <sanguis/aura_type_fwd.hpp>
#include <sanguis/buff_type_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/collision/world/object_unique_ptr.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/top_result_fwd.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/server/angle_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/optional_base_ref_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/with_id_fwd.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/world/context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/entity_map.hpp>
#include <sanguis/server/world/entity_vector.hpp>
#include <sanguis/server/world/object_fwd.hpp>
#include <sanguis/server/world/pickup_spawner.hpp>
#include <sanguis/server/world/parameters_fwd.hpp>
#include <sanguis/server/world/sight_range_map.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

class object
:
	private
	sanguis::server::environment::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sanguis::server::world::parameters const &,
		sanguis::world_id,
		sanguis::creator::top_result const &,
		sanguis::server::world::difficulty,
		sanguis::world_name const &
	);

	~object();

	void
	update(
		sanguis::duration const &
	);

	sanguis::server::entities::optional_base_ref const
	insert(
		sanguis::server::entities::unique_ptr &&,
		sanguis::server::entities::insert_parameters const &
	)
	override;

	sanguis::server::environment::object &
	environment();

	sanguis::creator::opening_container const &
	openings() const;

	sanguis::world_id const
	world_id() const;
private:
	sanguis::server::entities::optional_base_ref const
	insert_with_id(
		sanguis::server::entities::unique_ptr &&,
		sanguis::server::entities::insert_parameters const &
	);

	sanguis::server::entities::optional_base_ref const
	insert_base(
		sanguis::server::entities::unique_ptr &&,
		sanguis::server::entities::insert_parameters const &
	);
public:
	void
	add_aura(
		sanguis::entity_id,
		sanguis::aura_type
	)
	override;

	void
	add_buff(
		sanguis::entity_id,
		sanguis::buff_type
	)
	override;

	void
	remove_buff(
		sanguis::entity_id,
		sanguis::buff_type
	)
	override;

	void
	weapon_changed(
		sanguis::entity_id,
		sanguis::optional_primary_weapon_type
	)
	override;

	void
	got_weapon(
		sanguis::server::player_id,
		sanguis::weapon_description const &
	)
	override;

	void
	remove_weapon(
		sanguis::server::player_id,
		sanguis::is_primary_weapon
	)
	override;

	void
	magazine_remaining(
		sanguis::server::player_id,
		sanguis::is_primary_weapon,
		sanguis::magazine_remaining
	)
	override;

	void
	angle_changed(
		sanguis::entity_id,
		sanguis::server::angle
	)
	override;

	void
	center_changed(
		sanguis::entity_id,
		sanguis::server::center
	)
	override;

	void
	speed_changed(
		sanguis::entity_id,
		sanguis::server::speed
	)
	override;

	void
	weapon_status_changed(
		sanguis::entity_id,
		sanguis::weapon_status
	)
	override;

	void
	health_changed(
		sanguis::entity_id,
		sanguis::server::health
	)
	override;

	void
	max_health_changed(
		sanguis::entity_id,
		sanguis::server::health
	)
	override;

	void
	exp_changed(
		sanguis::server::player_id,
		sanguis::server::exp
	)
	override;

	void
	level_changed(
		sanguis::server::player_id,
		sanguis::server::level
	)
	override;

	void
	pickup_chance(
		sanguis::server::pickup_probability,
		sanguis::server::entities::enemies::difficulty,
		sanguis::server::center const&
	)
	override;

	void
	request_transfer(
		sanguis::entity_id
	)
	override;

	sanguis::server::world::difficulty const
	difficulty() const
	override;

	sanguis::collision::world::object &
	collision_world() const
	override;

	sanguis::creator::grid const &
	grid() const
	override;

	sanguis::server::environment::load_context &
	load_context() const
	override;

	void
	add_sight_range(
		sanguis::server::player_id,
		sanguis::entity_id target_id
	)
	override;

	void
	remove_sight_range(
		sanguis::server::player_id,
		sanguis::entity_id target_id
	)
	override;

	void
	remove_player(
		sanguis::server::player_id
	)
	override;
private:
	// own functions
	void
	send_entity_specific(
		sanguis::entity_id,
		sanguis::messages::server::base const &
	);

	void
	send_player_specific(
		sanguis::server::player_id,
		sanguis::messages::server::base const &
	);

	void
	insert_spawns(
		sanguis::creator::spawn_container const &,
		sanguis::random_generator &
	);

	void
	insert_destructibles(
		sanguis::creator::destructible_container const &
	);

	sanguis::server::entities::with_id &
	entity(
		sanguis::entity_id
	);

	sanguis::world_id const id_;

	sanguis::creator::seed const seed_;

	sanguis::server::world::difficulty const difficulty_;

	sanguis::world_name const name_;

	sanguis::creator::name const generator_name_;

	sanguis::creator::grid const grid_;

	sanguis::creator::opening_container const openings_;

	sanguis::server::world::context &global_context_;

	sanguis::server::environment::load_context &load_context_;

	sanguis::collision::world::object_unique_ptr const collision_world_;

	sanguis::server::world::sight_range_map sight_ranges_;

	sanguis::server::world::entity_map entities_;

	sanguis::server::world::entity_vector server_entities_;

	sanguis::server::world::pickup_spawner pickup_spawner_;
};

}
}
}

#endif
