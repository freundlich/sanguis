#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED

#include "../entity.hpp"
#include "../fwd.hpp"
#include "../../../pickup_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class pickup : public entity {
public:
	pickup_type::type ptype() const;
protected:
	pickup(
		pickup_type::type,
		environment const &,
		messages::pos_type const &,
		messages::space_unit angle,
		messages::space_unit direction,
		team::type team);
private:
	void update(
		time_type time,
		container &entities);
	virtual void do_pickup(
		entity_with_weapon &receiver) = 0;

	messages::dim_type const dim() const;
	entity_type::type type() const;
	bool invulnerable() const;

	pickup_type::type ptype_;
};

}
}
}
}

#endif
