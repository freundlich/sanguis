#ifndef SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED

#include "weapon.hpp"
#include "../../time_type.hpp"
#include "../../messages/types.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class melee : public weapon {
public:
	melee(
		messages::space_unit range,
		time_type base_cooldown,
		messages::space_unit damage);
private:
	void do_attack(
		entity const &from,
		messages::pos_type const&);
	messages::space_unit damage;
};

}
}
}

#endif
