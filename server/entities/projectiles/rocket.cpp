#include "rocket.hpp"
#include "aoe_damage.hpp"
#include "../../get_dim.hpp"
#include "../../../load/context.hpp"
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::rocket::rocket(
	server::environment const &env,
	pos_type const &center,
	space_unit const angle,
	team::type const team_,
	space_unit const damage,
	space_unit const aoe)
:
	projectile(
		projectile_type::rocket,
		env,
		center,
		angle,
		team_,
		boost::assign::map_list_of
			(
				entities::property::type::health,
				entities::property(messages::mu(1))
			)
			(
				entities::property::type::movement_speed,
				entities::property(messages::mu(300))
			),
		default_dim(
			env.load().models(),
			SGE_TEXT("rocket")),
		static_cast<time_type>(10)),
	damage(damage),
	aoe(aoe)
{}

void sanguis::server::entities::projectiles::rocket::do_hit(
	hit_vector const &)
{
	die();
}

void sanguis::server::entities::projectiles::rocket::do_die()
{
	damage_array const damage_values =
		boost::assign::list_of
		(messages::mu(0))
		(messages::mu(1))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0));
	
	insert(
		auto_ptr(
			new aoe_damage(
				environment(),
				center(),
				team(),
				aoe,
				damage,
				1,
				static_cast<time_type>(0.1),
				damage_values)));
}
