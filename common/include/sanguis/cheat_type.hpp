#ifndef SANGUIS_CHEAT_TYPE_HPP_INCLUDED
#define SANGUIS_CHEAT_TYPE_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>


namespace sanguis
{

enum class cheat_type
{
	exp,
	heal,
	kill,
	monster_pickup,
	monster_spawner,
	perks,
	rocket_launcher,
	sentry_pickup,
	shotgun,
	grenade_pickup,
	fcppt_maximum = grenade_pickup
};

}

#endif