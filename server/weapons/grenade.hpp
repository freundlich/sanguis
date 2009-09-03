#ifndef SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
#include "base_cooldown.hpp"
#include "cast_point.hpp"
#include "reload_time.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class grenade : public weapon {
public:
	grenade(
		server::environment const &,
		weapon_type::type,
		weapons::base_cooldown,
		space_unit damage,
		space_unit radius,
		weapons::cast_point,
		weapons::reload_time
	);
private:
	void do_attack(
		delayed_attack const &);
	
	space_unit const
		damage,
		radius;
};

}
}
}

#endif
