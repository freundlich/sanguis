#ifndef SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED

#include "../types.hpp"
#include <sge/collision/objects/circle_fwd.hpp>
#include <sge/collision/world_fwd.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class base {
	SGE_NONCOPYABLE(base)
protected:
	explicit base(
		sge::collision::world_ptr const collision_,
		pos_type const &center,
		pos_type const &speed,
		space_unit const radius);
	
	sge::collision::objects::circle_ptr const
	circle();

	sge::collision::objects::const_circle_ptr const
	circle() const;
public:
	virtual ~base();

	virtual bool
	can_collide_with(
		collision::base const &) const;

	virtual void
	collision(
		collision::base &);
private:
	sge::collision::objects::circle_ptr const circle_;
};

}
}
}

#endif