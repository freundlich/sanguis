#include <sanguis/entity_id.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/player_center_callback.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters.hpp>
#include <sanguis/client/draw2d/message/environment.hpp>
#include <sanguis/client/draw2d/scene/message_environment.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::message_environment::message_environment(
	sanguis::client::draw2d::scene::object &_object,
	sanguis::client::draw2d::scene::world::object &_world,
	sanguis::client::player_health_callback const &_player_health_callback
)
:
	sanguis::client::draw2d::message::environment(),
	object_(
		_object
	),
	world_(
		_world
	),
	player_health_callback_(
		_player_health_callback
	)
{
}

sanguis::client::draw2d::scene::message_environment::~message_environment()
{
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::message_environment::insert(
	sanguis::client::draw2d::entities::unique_ptr &&_entity,
	sanguis::entity_id const _id
)
{
	return
		object_.insert(
			std::move(
				_entity
			),
			_id
		);
}

void
sanguis::client::draw2d::scene::message_environment::remove(
	sanguis::entity_id const _id
)
{
	object_.remove(
		_id
	);
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::message_environment::entity(
	sanguis::entity_id const _id
)
{
	return
		object_.entity(
			_id
		);
}

void
sanguis::client::draw2d::scene::message_environment::change_world(
	sanguis::client::world_parameters const &_param
)
{
	object_.change_world(
		_param
	);
}

sanguis::client::draw2d::entities::model::load_parameters const
sanguis::client::draw2d::scene::message_environment::model_parameters() const
{
	return
		sanguis::client::draw2d::entities::model::load_parameters(
			object_.diff_clock(),
			object_.random_generator(),
			object_.sound_manager(),
			object_.colored_system(),
			object_.normal_system(),
			object_.load_collection()
		);
}

sanguis::client::load::auras::context &
sanguis::client::draw2d::scene::message_environment::aura_resources() const
{
	return
		object_.aura_resources();
}

sanguis::client::draw2d::insert_own_callback const &
sanguis::client::draw2d::scene::message_environment::insert_own_callback() const
{
	return
		object_.insert_own_callback();
}

sanguis::client::draw2d::player_center_callback const &
sanguis::client::draw2d::scene::message_environment::player_center_callback() const
{
	return
		object_.player_center_callback();
}

sanguis::client::draw2d::collide_callback const &
sanguis::client::draw2d::scene::message_environment::collide_callback() const
{
	return
		world_.collide_callback();
}

sanguis::client::player_health_callback const &
sanguis::client::draw2d::scene::message_environment::player_health_callback() const
{
	return
		player_health_callback_;
}