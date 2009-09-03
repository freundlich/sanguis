#ifndef SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
#include "base_cooldown.hpp"
#include "magazine_size.hpp"
#include "reload_time.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{
class rocket_launcher : public weapon {
public:
	rocket_launcher(
		server::environment const &,
		weapon_type::type,
		weapons::base_cooldown,
		space_unit rocket_damage,
		space_unit rocket_aoe,
		weapons::magazine_size,
		weapons::reload_time
	);
private:
	void do_attack(
		delayed_attack const &);
	
	space_unit rocket_damage,
	           rocket_aoe;
};

}
}
}

#endif
