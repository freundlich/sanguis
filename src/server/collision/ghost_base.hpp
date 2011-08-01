#ifndef SANGUIS_SERVER_COLLISION_GHOST_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_BASE_HPP_INCLUDED

#include "body_base_fwd.hpp"
#include "body_enter_callback.hpp"
#include "body_exit_callback.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/logic/tribool_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class ghost_base
{
	FCPPT_NONCOPYABLE(
		ghost_base
	);
protected:
	ghost_base();

	virtual ~ghost_base();
	
	virtual boost::logic::tribool const
	can_collide_with(
		collision::body_base const &
	) const = 0;

	collision::body_enter_callback const
	body_enter_callback();

	collision::body_exit_callback const
	body_exit_callback();
private:
	void
	collision_begin(
		collision::body_base &
	);

	void
	collision_end(
		collision::body_base &
	);

	virtual void
	body_enter(
		collision::body_base &
	) = 0;

	virtual void
	body_exit(
		collision::body_base &
	) = 0;
};

}
}
}

#endif