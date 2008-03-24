#include "running_state.hpp"
#include "waiting_state.hpp"
#include "get_unique_id.hpp"
#include "../messages/player_rotation_event.hpp"
#include "../messages/player_direction_event.hpp"
#include "../messages/add.hpp"
#include "../messages/game_state.hpp"
#include "../messages/player_state.hpp"
#include "../messages/client_info.hpp"
#include "../messages/rotate.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/move.hpp"
#include "../messages/speed.hpp"
#include "../entity_type.hpp"
#include "../game_state.hpp"
#include "../dispatch_type.hpp"
#include "../truncation_check_cast.hpp"
#include "../truncation_check_structure_cast.hpp"
#include "message_functor.hpp"

#include <sge/iostream.hpp>
#include <sge/su.hpp>
#include <sge/string.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/atan2.hpp>

#include <boost/bind.hpp>
#include <boost/mpl/vector.hpp>

#include <cmath>
#include <cassert>

sanguis::server::running_state::running_state()
	: player_speed(SGE_TEXT("player_speed"),sge::su(0.1)),
	  send_timer(sge::second()),
		message_freq(SGE_TEXT("message_freq"),
			boost::bind(&running_state::set_message_freq,this,_1,_2),sge::su(0.5))
{
	sge::clog << SGE_TEXT("server: entering running state\n");
}

sge::space_unit sanguis::server::running_state::set_message_freq(const sge::space_unit,const sge::space_unit newv)
{
	send_timer.interval(static_cast<sge::time_type>(static_cast<sge::space_unit>(sge::second())*newv));
	return newv;
}

boost::statechart::result sanguis::server::running_state::react(const tick_event&t) 
{
	const sge::timer::frames_type delta = t.data.diff_time;

	bool update_pos = send_timer.update_b();

	for (player_map::iterator i = players.begin(); i != players.end(); ++i)
	{
		i->second.pos += i->second.speed * static_cast<messages::space_unit>(delta);

		if (update_pos)
			context<machine>().send(
				new messages::move(i->second.id,sge::math::structure_cast<messages::space_unit>(i->second.pos)));
	}

	return discard_event();
}

void sanguis::server::running_state::create_game(const net::id_type id,const messages::client_info &m)
{
	assert(!players.size());

	player_type &player = players[id];

	player.id =     get_unique_id();
	player.name =   m.name;
	player.pos =    messages::pos_type(static_cast<messages::space_unit>(0.5),static_cast<messages::space_unit>(0.5));
	player.angle =  static_cast<messages::space_unit>(0);

	sge::cout << "server: player.pos=" << player.pos << "\n";

	// send player entity, game state and player state
	sge::clog << SGE_TEXT("server: sending game messages\n");
	context<machine>().send(new messages::game_state(game_state(truncation_check_cast<boost::uint32_t>(0))));
	context<machine>().send(
		new messages::add(player.id,
			entity_type::player,
			player.pos,
			player.angle,messages::vector2()));
	context<machine>().send(new messages::player_state(player.id,player_state(weapon_type::pistol,truncation_check_cast<boost::uint32_t>(0))));
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_rotation_event &e)
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: got rotation_event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	player_type &player = players[id];
	player.angle = e.angle();
	context<machine>().send(new messages::rotate(player.id,player.angle));
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_direction_event &e)
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("server: got direction_event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	player_type &player = players[id];

	if (e.dir().is_null())
		player.speed = sge::math::vector2();
	else
		player.speed = sge::math::normalize(e.dir()) * player_speed.value();

	context<machine>().send(new messages::speed(player.id,player.speed));
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::client_info&m) 
{
	if (players.size())
	{
		sge::clog << SGE_TEXT("server: got superfluous client info from id ") << id << SGE_TEXT("\n");
		return discard_event();
	}
	sge::clog << SGE_TEXT("server: received client info from ") << id << SGE_TEXT("\n");
	create_game(id,m);
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::disconnect&) 
{
	if (players.find(id) == players.end())
	{
		sge::clog << SGE_TEXT("spectator ") << id << SGE_TEXT(" disconnected\n");
		return discard_event();
	}
	sge::clog << SGE_TEXT("server: disconnected\n");
	return transit<waiting_state>();
}

boost::statechart::result sanguis::server::running_state::handle_default_msg(const net::id_type id,const messages::base&m) 
{
	sge::clog << SGE_TEXT("server: received unexpected message ") << typeid(m).name() << SGE_TEXT(" from id ") << id << SGE_TEXT("\n");
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::react(const message_event&m) 
{
	message_functor<running_state> mf(*this,m.id);

	return dispatch_type<
		boost::mpl::vector<
			messages::disconnect,
			messages::client_info,
			messages::player_rotation_event,
			messages::player_direction_event
		>,
		boost::statechart::result>(
		mf,
		*m.message,
		boost::bind(&running_state::handle_default_msg, this, m.id, _1));
}
