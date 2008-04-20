#ifndef SANGUIS_SERVER_ENTITY_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITY_WITH_WEAPON_HPP_INCLUDED

#include "entity.hpp"
#include "weapons/weapon.hpp"

namespace sanguis
{
namespace server
{

class entity_with_weapon : public entity {
protected:
	entity_with_weapon(
		messages::pos_type const &pos,
		const messages::space_unit angle,
		const messages::space_unit direction,
		const messages::space_unit health,
		const messages::space_unit max_health,
		const team::type team,
		const messages::space_unit speed,
		weapons::weapon_ptr);
	virtual void update(const time_type);
public:
	void change_weapon(weapons::weapon_ptr);
	void target(
		messages::pos_type const&);
	messages::pos_type const &target() const;
private:
	weapons::weapon_ptr weapon_;
	messages::pos_type  target_;
};

}
}

#endif
