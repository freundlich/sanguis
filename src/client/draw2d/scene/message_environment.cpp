#include "message_environment.hpp"
#include "object.hpp"
#include "hud.hpp"
#include "../entities/model/parameters.hpp"
#include "../entities/base.hpp"

sanguis::client::draw2d::scene::message_environment::message_environment(
	scene::object &_object,
	hud &_hud
)
:
	object_(_object),
	hud_(_hud)
{
}

sanguis::client::draw2d::scene::message_environment::~message_environment()
{
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::message_environment::insert(
	entities::unique_ptr _entity,
	entity_id const _id
)
{
	return 
		object_.insert(
			move(
				_entity
			),
			_id
		);
}

void
sanguis::client::draw2d::scene::message_environment::remove(
	entity_id const _id
)
{
	object_.remove(
		_id
	);
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::message_environment::entity(
	entity_id const _id
)
{
	return
		object_.entity(
			_id
		);
}

void
sanguis::client::draw2d::scene::message_environment::experience(
	client::exp const _exp
)
{
	hud_.experience(
		_exp
	);
}

void
sanguis::client::draw2d::scene::message_environment::level(
	client::level const _level
)
{
	hud_.level(
		_level
	);
}

sanguis::client::draw2d::entities::model::parameters const
sanguis::client::draw2d::scene::message_environment::model_parameters() const
{
	return
		entities::model::parameters(
			object_.colored_system(),
			object_.normal_system(),
			object_.load_collection()
		);
}

sanguis::client::draw2d::sprite::particle::system &
sanguis::client::draw2d::scene::message_environment::particle_system() const
{
	return object_.particle_system();
}

sanguis::client::draw2d::insert_own_callback const &
sanguis::client::draw2d::scene::message_environment::insert_own_callback() const
{
	return object_.insert_own_callback();
}

sanguis::client::draw2d::transform_callback const &
sanguis::client::draw2d::scene::message_environment::transform_callback() const
{
	return object_.transform_callback();
}
