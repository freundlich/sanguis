#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_SHOOT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_SHOOT_HPP_INCLUDED

#include "shoot_fwd.hpp"
#include "../../entities/entity_with_weapon_fwd.hpp"
#include "../../pos_type.hpp"
#include <sge/math/vector/basic_decl.hpp>
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace events
{

class shoot
:
	public boost::statechart::event<
		shoot
	>
{
public:
	shoot(
		entities::entity_with_weapon &from,
		pos_type const &to);
	
	entities::entity_with_weapon &
	from() const;

	pos_type const &
	to() const;
private:
	entities::entity_with_weapon &from_;
	pos_type const to_;
};

}
}
}
}

#endif