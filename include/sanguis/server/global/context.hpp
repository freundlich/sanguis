#ifndef SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>
#include <sanguis/connect_state_fwd.hpp>
#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/load/server_context_fwd.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/console_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/vector_fwd.hpp>
#include <sanguis/server/entities/player_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/global/context_fwd.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
#include <sanguis/server/global/world_map.hpp>
#include <sanguis/server/world/context.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace global
{

class context
:
	public sanguis::server::world::context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context(
		sanguis::server::unicast_callback const &,
		sanguis::load::server_context const &,
		sanguis::server::console &
	);

	~context();

	void
	insert_player(
		sanguis::world_id,
		sanguis::server::player_id,
		sanguis::server::string const &name,
		sanguis::connect_state
	);

	void
	player_disconnect(
		sanguis::server::player_id
	);

	void
	player_target(
		sanguis::server::player_id,
		sanguis::server::vector const &
	);

	void
	player_change_world(
		sanguis::server::player_id
	);

	void
	player_change_shooting(
		sanguis::server::player_id,
		bool shooting,
		sanguis::is_primary_weapon
	);

	void
	player_reload(
		sanguis::server::player_id,
		sanguis::is_primary_weapon
	);

	void
	player_drop_or_pickup_weapon(
		sanguis::server::player_id,
		sanguis::is_primary_weapon
	);

	void
	player_speed(
		sanguis::server::player_id,
		sanguis::server::speed const &
	);

	void
	player_position(
		sanguis::server::player_id,
		sanguis::server::center const &
	);

	void
	player_cheat(
		sanguis::server::player_id,
		sanguis::cheat_type
	);

	void
	player_choose_perk(
		sanguis::server::player_id,
		sanguis::perk_type
	);

	void
	update(
		sanguis::duration const &
	);

	bool
	multiple_players() const;

	bool
	has_player(
		sanguis::server::player_id
	) const;
private:
	sanguis::entity_id const
	next_id();

	// callbacks for world

	void
	send_to_player(
		sanguis::server::player_id,
		sanguis::messages::base const &
	)
	override;

	void
	remove_player(
		sanguis::server::player_id
	)
	override;

	bool
	request_transfer(
		sanguis::server::global::source_world_pair
	) const
	override;

	void
	transfer_entity(
		sanguis::server::global::source_world_pair,
		sanguis::server::entities::unique_ptr &&
	)
	override;

	sanguis::server::world::object &
	world(
		sanguis::world_id
	);

	sanguis::server::entities::player &
	player(
		sanguis::server::player_id
	);

	sanguis::diff_clock diff_clock_;

	sanguis::random_generator random_generator_;

	sanguis::entity_id next_id_;

	sanguis::server::unicast_callback const send_unicast_;

	typedef
	fcppt::scoped_ptr<
		sanguis::server::environment::load_context
	>
	load_context_scoped_ptr;

	load_context_scoped_ptr const load_context_;

	sanguis::server::console &console_;

	typedef
	std::unordered_map<
		sanguis::server::player_id,
		sanguis::server::entities::player *
	>
	player_map;

	player_map players_;

	sanguis::server::global::world_map const worlds_;
};

}
}
}

#endif
