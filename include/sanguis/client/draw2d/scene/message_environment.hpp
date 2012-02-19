#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/message_environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/hud_fwd.hpp>
#include <sanguis/client/draw2d/scene/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/client/draw2d/message/environment.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

class message_environment
:
	public draw2d::message::environment
{
	FCPPT_NONCOPYABLE(
		message_environment
	);
public:
	message_environment(
		scene::object &,
		scene::hud &,
		scene::world::object &
	);

	~message_environment();
private:
	entities::base &
	insert(
		entities::unique_ptr,
		entity_id
	);

	void
	remove(
		sanguis::entity_id
	);

	entities::base &
	entity(
		sanguis::entity_id
	);

	void
	experience(
		client::exp
	);

	void
	level(
		client::level
	);

	void
	change_world(
		client::world_parameters const &
	);

	entities::model::parameters const
	model_parameters() const;

	sprite::particle::system &
	particle_system() const;

	draw2d::insert_own_callback const &
	insert_own_callback() const;

	draw2d::transform_callback const &
	transform_callback() const;

	scene::object &object_;

	scene::hud &hud_;

	scene::world::object &world_;
};

}
}
}
}

#endif