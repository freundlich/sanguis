#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED

#include "../entity.hpp"
#include "../fwd.hpp"
#include "../../../pickup_type.hpp"
#include <boost/optional.hpp>

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
	
	bool can_collide_with(entity const &) const;
	void collision(entity &);
protected:
	typedef boost::optional<dim_type> optional_dim;

	pickup(
		pickup_type::type,
		server::environment const &,
		pos_type const &center,
		team::type team,
		optional_dim const &dim
			= optional_dim());
private:
	// TODO: is it ok that pickups are limited to entities with weapons?
	virtual void do_pickup(
		entity_with_weapon &receiver) = 0;

	messages::auto_ptr add_message() const;

	pickup_type::type ptype_;
};

}
}
}
}

#endif
