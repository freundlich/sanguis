#include "simple.hpp"
#include "../entities/entity_with_weapon.hpp"
#include <sge/math/angle.hpp>
#include <boost/foreach.hpp>

sanguis::server::ai::simple::simple()
: target(0)
{}

void sanguis::server::ai::simple::update(
	entities::entity_with_weapon &me,
	time_type,
	entities::container const &entities)
{
	if(!target)
	{
		BOOST_FOREACH(
			entities::entity const &e,
			entities)
		{
			if(!e.invulnerable() && e.team() != me.team())
				target = &e;
		}
	}
	else
	{
		// TODO: why can't we use std::find here?
		for(entities::container::const_iterator it(entities.begin()); it != entities.end(); ++it)
			if(&*it == target)
				break;
		target = 0;
	}

	if(!target)
		return;

	const boost::optional<messages::space_unit> angle(
		sge::math::angle_to<messages::space_unit>(
			me.center(),
			target->center()));
	if(angle)
	{
		me.direction(*angle);
		me.angle(*angle);
	}
	// TODO: movement speed is always at full speed by default
	//me.get_property(sanguis::server::entity::property::type::speed).current(messages::mu(1));
	me.target(
		target->center());
	me.aggressive(true);
}
