#ifndef SANGUIS_SERVER_ENTITY_WITH_AI_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITY_WITH_AI_HPP_INCLUDED

#include "entity_with_weapon.hpp"
#include "../ai/base.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class entity_with_ai : public entity_with_weapon {
protected:
	entity_with_ai(
		environment const &,
		armor_array const &,
		messages::pos_type const &pos,
		messages::space_unit angle,
		messages::space_unit direction,
		team::type team_,
		entity::property_map const &,
		ai::ai_ptr ai_,
		weapons::weapon_ptr start_weapon
			= weapons::weapon_ptr());
	
	virtual void update(
		time_type,
		container &entities);
private:
	ai::ai_ptr ai_;
};

}
}
}

#endif
