#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED

#include "pickup.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class health : public pickup {
public:
	health(
		environment const &,
		messages::pos_type const &,
		team::type team,
		messages::space_unit amount);
private:
	void do_pickup(
		entity_with_weapon &receiver);
	
	messages::dim_type const dim() const;

	messages::space_unit amount;
};

}
}
}
}

#endif
