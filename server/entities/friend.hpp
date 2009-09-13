#ifndef SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED

#include "entity_with_ai.hpp"
#include "../../friend_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class friend_ : public entity_with_ai {
public:
	friend_(
		friend_type::type,
		server::environment::object_ptr,
		damage::armor const &,
		pos_type const &center,
		space_unit angle,
		space_unit direction,
		team::type,
		property_map const &,
		ai::auto_ptr,
		weapons::auto_ptr weapon
	);
private:
	messages::auto_ptr
	add_message() const;

	boost::logic::tribool const
	can_collide_with_entity(
		entity const &
	) const;

	friend_type::type const ftype_;
};

}
}
}

#endif
