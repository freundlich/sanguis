#ifndef SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED

#include "context_fwd.hpp"
#include "player_map.hpp"
#include "world_context_fwd.hpp"
#include "../world/map.hpp"
#include "../world/context_fwd.hpp"
#include "../entities/auto_ptr.hpp"
#include "../unicast_callback.hpp"
#include "../string.hpp"
#include "../player_id.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include "../../cheat_type.hpp"
#include "../../connect_state.hpp"
#include "../../weapon_type.hpp"
#include "../../world_id.hpp"
#include "../../perk_type.hpp"
#include "../../time_type.hpp"
#include "../../messages/auto_ptr.hpp"
#include "../../load/model/context_fwd.hpp"
#include <sge/log/logger_fwd.hpp>
#include <sge/container/map_decl.hpp>
#include <sge/collision/system_fwd.hpp>
#include <sge/shared_ptr.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace global
{

class context {
	SGE_NONCOPYABLE(context)
public:
	context(
		unicast_callback const &,
		sge::collision::system_ptr,
		load::model::context const &
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
private:
	friend class world_context;

	// callbacks for world

	void
	send_to_player(
		world_id,
		messages::auto_ptr
	);

	void
	remove_player(
		player_id
	);

	void
	transfer_entity(
		world_id destination,
		entities::auto_ptr
	);

	server::world::object &
	world(
		world_id
	);

	static sge::log::logger &
	log();

	unicast_callback const send_unicast_;
	
	world::map worlds_;
	
	player_map players_;

	load::model::context const &model_context_;

	sge::shared_ptr<
		world::context
	> const world_context_;
};

}
}
}

#endif
