#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "healthbar_fwd.hpp"
#include "decay_time_fwd.hpp"
#include "part_fwd.hpp"
#include "parameters_fwd.hpp"
#include "needs_healthbar.hpp"
#include "decay_option.hpp"
#include "../container.hpp"
#include "../with_health.hpp"
#include "../with_weapon.hpp"
#include "../../sprite/index_fwd.hpp"
#include "../../sprite/order.hpp"
#include "../../sprite/rotation_type.hpp"
#include "../../vector2.hpp"
#include "../../../health_type.hpp"
#include "../../../../animation_type.hpp"
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

class object 
:
	public container,
	public with_health,
	public with_weapon
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		parameters const &,
		fcppt::string const &name,
		sprite::order,
		needs_healthbar::type,
		decay_option::type
	);

	~object();

	// with_health overrides
	health_type
	max_health() const;

	health_type
	health() const;
protected:
	virtual void
	update(
		time_type
	);

	// with_orientation overrides
	virtual void
	orientation(
		sprite::rotation_type
	);

	using container::orientation;

	void
	orientation(
		sprite::rotation_type,
		size_type index
	);
	
	// base overrides
	bool
	is_decayed() const;
	
	virtual void
	on_decay();

	// with_speed overrides
	virtual void
	speed(
		vector2 const &
	);

	using container::speed;

	model::part &
	part(
		sprite::index const &
	);

	bool
	dead() const;

	bool
	walking() const;

	bool
	has_health() const;
private:
	// with_health overrides
	void
	health(
		health_type
	);

	void
	max_health(
		health_type
	);

	// with_weapon overrides
	void
	weapon(
		weapon_type::type
	);

	void
	attacking(
		bool
	);

	void
	reloading(
		bool
	);

	// own functions
	void
	change_animation();

	void
	change_animation(
		animation_type::type
	);

	animation_type::type
	animation() const;

	animation_type::type
	fallback_anim(
		animation_type::type
	) const;

	void
	update_healthbar();

	bool
	animations_ended() const;

	static fcppt::log::object &
	log();

	bool
		attacking_,
		reloading_;

	health_type
		health_,
		max_health_;

	fcppt::scoped_ptr<
		healthbar
	> healthbar_;

	fcppt::scoped_ptr<
		decay_time
	> decay_time_;

	decay_option::type const decay_option_;

	typedef boost::ptr_vector<
		model::part
	> part_vector;

	part_vector parts_;
};

}
}
}
}
}

#endif
