#include "object.hpp"
#include "part.hpp"
#include "../../log.hpp"
#include "../../sprite/index.hpp"
#include "../../../id_dont_care.hpp"
#include "../../../../load/model/collection.hpp"
#include "../../../../load/model/context.hpp"
#include "../../../../load/context.hpp"
#include "../../../../exception.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>
#include <ostream>

sanguis::client::draw2d::entities::model::object::object(
	draw::environment const &env,
	entity_id const id,
	fcppt::string const &name,
	sprite::order const order,
	bool const show_healthbar,
	draw::remove_action::type const remove_action_
)
:
	container(
		env,
		id,
		env.context().models()()[name].size(),
		order
	),
	attacking(false),
	reloading(false),
	health_(0),
	max_health_(0),
	healthbar_(
		show_healthbar
		?
			new healthbar(
				env
			)
		:
			0
	),
	remove_action_(remove_action_)
{
	part_vector::size_type i(0);

	BOOST_FOREACH(
		load::model::model::value_type const &p,
		env.context().models()()[name]
	)
		parts.push_back(
			new model_part(
				p.second,
				at(sprite_part_index(i++))
			)
		);
	
	change_animation(
		animation_type::deploying
	);
}

sanguis::client::draw2d::entities::model::object::~model()
{}

sanguis::draw::funit
sanguis::client::draw2d::entities::model::object::max_health() const
{
	return max_health_;
}

sanguis::draw::funit
sanguis::client::draw2d::entities::model::object::health() const
{
	return health_;
}

void sanguis::client::draw2d::entities::model::object::update(
	time_type const time)
{
	container::update(time);

	if(healthbar_)
		healthbar_->attach_to(
			master().pos(),
			master().size());

	BOOST_FOREACH(model_part &p, parts)
		p.update(time);
}

void sanguis::client::draw2d::entities::model::object::orientation(
	sprite::rotation_type const rot)
{
	BOOST_FOREACH(model_part &p, parts)
		p.orientation(rot);
}

void sanguis::client::draw2d::entities::model::object::orientation(
	sprite::rotation_type const rot,
	size_type const index)
{
	parts.at(index).orientation(rot);	
}

bool sanguis::client::draw2d::entities::model::object::may_be_removed() const
{
	return entity::may_be_removed()
		&& animations_ended();
}

sanguis::draw::remove_action::type
sanguis::client::draw2d::entities::model::object::remove_action() const
{
	return remove_action_; 
}

void sanguis::client::draw2d::entities::model::object::speed(
	vector2 const &s)
{
	vector2 const old_speed(
		speed());
	
	container::speed(s);

	if(is_null(s) != is_null(old_speed))
		change_animation();
}

sanguis::client::draw2d::entities::model::object_part &
sanguis::client::draw2d::entities::model::object::part(
	sprite_part_index const &idx)
{
	return parts.at(idx.get());
}

bool sanguis::client::draw2d::entities::model::object::dead() const
{
	return health() <= 0;
}

bool sanguis::client::draw2d::entities::model::object::walking() const
{
	return !is_null(speed());
}

bool sanguis::client::draw2d::entities::model::object::has_health() const
{
	return max_health() > 0;
}

void sanguis::client::draw2d::entities::model::object::health(
	funit const health)
{
	health_ = health;
	update_healthbar();
	
	if(!dead())
		return;
	
	healthbar_.reset();
	change_animation();
	speed(vector2::null()); // FIXME
}

void sanguis::client::draw2d::entities::model::object::max_health(
	funit const max_health)
{
	max_health_ = max_health;
	update_healthbar();
}

void sanguis::client::draw2d::entities::model::object::weapon(
	weapon_type::type const weapon_)
{
	BOOST_FOREACH(model_part &p, parts)
		p.weapon(weapon_);
	change_animation();
}

void sanguis::client::draw2d::entities::model::object::start_attacking()
{
	if(attacking)
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_ << FCPPT_TEXT("start_attacking(): already attacking!"));
	attacking = true;

	change_animation();
}

void sanguis::client::draw2d::entities::model::object::stop_attacking()
{
	if(!attacking)
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_ << FCPPT_TEXT("stop_attacking(): already not attacking!"));
	attacking = false;

	change_animation();
}

void sanguis::client::draw2d::entities::model::object::start_reloading()
{
	if(reloading)
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_ << FCPPT_TEXT("start_reloading(): already reloading!"));
	reloading = true;

	change_animation();
}

void sanguis::client::draw2d::entities::model::object::stop_reloading()
{
	if(!reloading)
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_ << FCPPT_TEXT("stop_reloading(): already not reloading!"));
	reloading = false;

	change_animation();
}

void sanguis::client::draw2d::entities::model::object::change_animation()
{
	change_animation(
		animation());
}

void sanguis::client::draw2d::entities::model::object::change_animation(
	animation_type::type const nanim)
{
	BOOST_FOREACH(model_part &p, parts)
	{
		animation_type::type part_anim(
			nanim);
		while(!p.try_animation(part_anim))
			part_anim = fallback_anim(part_anim);
	}
}

sanguis::animation_type::type
sanguis::client::draw2d::entities::model::object::fallback_anim(
	animation_type::type const anim) const
{
	switch(anim) {
	case animation_type::none:
		return animation_type::size;
	case animation_type::attacking:
	case animation_type::reloading:
		return walking()
		? animation_type::walking
		: animation_type::none;
	case animation_type::deploying:
	case animation_type::walking:
	case animation_type::dying:
		return animation_type::none;
	default:
		throw exception(
			FCPPT_TEXT("Invalid animation in fallback_anim!"));
	}
}

sanguis::animation_type::type
sanguis::client::draw2d::entities::model::object::animation() const
{
	return
		dead()
		?
			animation_type::dying
		:
			reloading
			?
				animation_type::reloading
			:
				attacking
				?
					animation_type::attacking
				:
					is_null(container::speed())
					?
						animation_type::none
					:
						animation_type::walking;
}

void
sanguis::client::draw2d::entities::model::object::update_healthbar()
{
	if(!healthbar_)
		return;
	
	healthbar_->update_health(
		health(),
		max_health()
	);
}

bool
sanguis::client::draw2d::entities::model::object::animations_ended() const
{
	BOOST_FOREACH(
		part_vector::const_reference part,
		parts
	)
		if(!part.animation_ended())
			return false;
	return true;
}

fcppt::log::object &
sanguis::client::draw2d::entities::model::object::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			draw::log(),
			FCPPT_TEXT("model")
		)
	);
	return log_;
}