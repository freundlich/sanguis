#ifndef SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class pistol : public weapon {
public:
	pistol(
		server::environment const &,
		weapon_type::type,
		time_type base_cooldown,
		space_unit damage,
		time_type cast_point,
		unsigned magazine_size,
		time_type reload_time,
		space_unit range
	);
private:
	void do_attack(
		delayed_attack const &);

	space_unit const damage;
};

}
}
}

#endif
