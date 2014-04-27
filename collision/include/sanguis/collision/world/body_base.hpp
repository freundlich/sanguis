#ifndef SANGUIS_COLLISION_WORLD_BODY_BASE_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_BASE_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <fcppt/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class FCPPT_CLASS_SYMBOL body_base
{
	FCPPT_NONCOPYABLE(
		body_base
	);
protected:
	SANGUIS_COLLISION_SYMBOL
	body_base();
public:
	SANGUIS_COLLISION_SYMBOL
	virtual
	~body_base() = 0;

	virtual
	boost::logic::tribool const
	can_collide_with(
		sanguis::collision::world::body_base const &
	) const = 0;

	virtual
	void
	collision(
		sanguis::collision::world::body_base &
	) = 0;
};

}
}
}

#endif