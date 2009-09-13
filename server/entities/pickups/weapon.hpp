#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_HPP_INCLUDED

#include "pickup.hpp"
#include "../entity_with_weapon_fwd.hpp"
#include "../../environment/object_ptr.hpp"
#include "../../pos_type.hpp"
#include "../../team.hpp"
#include "../../../weapon_type.hpp"
#include "../../../messages/auto_ptr.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class weapon : public pickup {
public:
	weapon(
		server::environment::object_ptr,
		pos_type const &center,
		team::type team,
		weapon_type::type
	);
	
	weapon_type::type
	wtype() const;
private:
	messages::auto_ptr
	add_message() const;

	void
	do_pickup(
		entity_with_weapon &receiver
	);

	weapon_type::type const weapon_type_;
};

}
}
}
}

#endif
