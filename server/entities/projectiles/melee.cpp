#include "melee.hpp"
#include "../property.hpp"
#include "../../damage/list.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/normal.hpp"
#include "../../damage/full.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/optional_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::melee::melee(
	server::environment::object_ptr const env,
	pos_type const &center,
	team::type const team_,
	space_unit const damage)
:
	projectile(
		projectile_type::melee,
		env,
		center,
		static_cast<space_unit>(0), // angle doesn't matter here
		team_,
		boost::assign::map_list_of
			(
				entities::property_type::health,
				entities::property(static_cast<space_unit>(1))
			)
			(
				entities::property_type::movement_speed,
				entities::property(static_cast<space_unit>(0))
			),
		dim_type(
			1,
			1
		),
		static_cast<time_type>(1), // short lifetime
		indeterminate::yes
	),
	damage(damage)
{}

void
sanguis::server::entities::projectiles::melee::do_damage(
	entity &e
)
{
	e.damage(
		damage,
		damage::list(
			damage::normal = damage::full
		)
	);

	die();
}
