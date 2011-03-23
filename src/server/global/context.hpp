#ifndef SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED

#include "context_fwd.hpp"
#include "world_context_fwd.hpp"
#include "../world/map.hpp"
#include "../world/context_ptr.hpp"
#include "../entities/unique_ptr.hpp"
#include "../entities/insert_parameters_fwd.hpp"
#include "../entities/player_map.hpp"
#include "../environment/load_context_ptr.hpp"
#include "../unicast_callback.hpp"
#include "../string.hpp"
#include "../player_id.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include "../console_fwd.hpp"
#include "../../cheat_type.hpp"
#include "../../connect_state.hpp"
#include "../../weapon_type.hpp"
#include "../../world_id.hpp"
#include "../../perk_type.hpp"
#include "../../time_type.hpp"
#include "../../messages/auto_ptr.hpp"
#include "../../load/context_base_fwd.hpp"
#include <sge/collision/system_ptr.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/container/map_decl.hpp>
#include <fcppt/shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace global
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context(
		unicast_callback const &,
		sge::collision::system_ptr,
		load::context_base const &,
		server::console &
	);

	~context();

	void
	insert_player(
		world_id,
		player_id,
		string const &name,
		connect_state::type
	);

	void
	player_disconnect(
		player_id
	);

	void
	player_target(
		player_id,
		pos_type const &
	);

	void
	player_change_weapon(
		player_id,
		weapon_type::type
	);

	void
	player_angle(
		player_id,
		space_unit
	);

	void
	player_change_shooting(
		player_id,
		bool shooting
	);

	void
	player_direction(
		player_id,
		pos_type const &
	);

	void
	player_cheat(
		player_id,
		cheat_type::type
	);

	void
	player_choose_perk(
		player_id,
		perk_type::type
	);

	void
	update(
		time_type
	);

	entities::player_map::size_type
	player_count() const;
private:
	friend class world_context;

	// callbacks for world

	void
	send_to_player(
		player_id,
		messages::auto_ptr
	);

	void
	remove_player(
		player_id
	);

	void
	transfer_entity(
		world_id destination,
		entities::unique_ptr,
		entities::insert_parameters const &
	);

	server::world::object &
	world(
		world_id
	);

	static fcppt::log::object &
	log();

	unicast_callback const send_unicast_;

	sge::collision::system_ptr const collision_system_;
	
	world::map worlds_;
	
	entities::player_map players_;

	server::world::context_ptr const world_context_;

	server::environment::load_context_ptr const load_context_;

	server::console &console_;
};

}
}
}

#endif