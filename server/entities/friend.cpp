#include "friend.hpp"
#include "base_parameters.hpp"
#include "../weapons/weapon.hpp"
#include "../ai/base.hpp"
#include "../get_dim.hpp"
#include "../../load/friend_name.hpp"
#include "../../load/context.hpp"
#include "../../messages/add_friend.hpp"
#include "../../messages/create.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

sanguis::server::entities::friend_::friend_(
	friend_type::type const ftype_,
	server::environment const &env,
	armor_array const &armor,
	pos_type const &center,
	space_unit const angle,
	space_unit const direction,
	team::type const team_,
	property_map const &properties,
	ai::auto_ptr ai_,
	weapons::auto_ptr weapon_)
:
	entity_with_ai(
		base_parameters(
			env,
			armor,
			center,
			angle,
			direction,
			team_,
			properties,
			entity_type::friend_,
			false,
			default_dim(
				env.load()().models(),
				load::friend_name(
					ftype_
				)
			)
		),
		ai_,
		weapon_
	),
	ftype_(ftype_)
{}

sanguis::messages::auto_ptr
sanguis::server::entities::friend_::add_message() const
{
	return messages::create(
		messages::add_friend(
			id(),
			pos(),
			angle(),
			abs_speed(),
			health(),
			max_health(),
			dim(),
			ftype_
		)
	);
}