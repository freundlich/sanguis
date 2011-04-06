#ifndef SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED

#include "with_body_fwd.hpp"
#include "body_parameters_fwd.hpp"
#include "transfer_parameters_fwd.hpp"
#include "with_ghosts.hpp"
#include "ifaces/with_body.hpp"
#include "../collision/body_base.hpp"
#include "../collision/body_fwd.hpp"
#include "../angle.hpp"
#include "../center.hpp"
#include "../speed.hpp"
#include <sge/projectile/body/scoped_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/logic/tribool_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_body
:
	public virtual entities::with_ghosts,
	protected virtual ifaces::with_body,
	public collision::body_base
{
	FCPPT_NONCOPYABLE(
		with_body
	);
public:
	explicit with_body(
		entities::body_parameters const &
	);

	~with_body();

	// entities::base overridden functions
	server::center const
	center() const;

	// own functions
	server::angle const
	angle() const;

	void
	center(
		server::center const &
	);

	void
	speed(
		server::speed const &
	);

	void
	angle(
		server::angle
	);
protected:
	void
	on_transfer(
		entities::transfer_parameters const &
	);
private:
	void
	on_position_change(
		server::center const &
	);

	boost::logic::tribool const
	can_collide_with(
		collision::body_base const &
	) const;

	void
	collide(
		collision::body_base &
	);

	virtual boost::logic::tribool const
	can_collide_with_body(
		entities::with_body const &
	) const;

	virtual void
	collision_with_body(
		entities::with_body &
	);

	void
	reset_speed(
		server::speed const &
	);

	typedef fcppt::scoped_ptr<
		collision::body
	> body_scoped_ptr;

	body_scoped_ptr collision_body_;

	typedef fcppt::scoped_ptr<
		sge::projectile::body::scoped
	> scoped_body_scope_ptr;

	scoped_body_scope_ptr scoped_body_;
};

}
}
}

#endif
