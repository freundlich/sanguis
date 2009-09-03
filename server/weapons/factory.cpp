#include "factory.hpp"
#include "pistol.hpp"
#include "shotgun.hpp"
#include "rocket_launcher.hpp"
#include "weapon.hpp"
#include "grenade.hpp"
#include "sentry.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>

sanguis::server::weapons::auto_ptr
sanguis::server::weapons::create(
	weapon_type::type const type,
	environment const &env)
{
	switch(type) {
	case weapon_type::melee:
		throw exception(
			SGE_TEXT("Please create melee weapons directly, not through the weapon factory!"));
	case weapon_type::pistol:
		return auto_ptr(
			new pistol(
				env,
				type,
				static_cast<time_type>(0.5),
				static_cast<space_unit>(5),
				static_cast<time_type>(0.2),
				18, // magazine size
				static_cast<time_type>(2) // reload time
			)
		);
	case weapon_type::dual_pistol:
		return auto_ptr(
			new pistol(
				env,
				type,
				static_cast<time_type>(0.33),
				static_cast<space_unit>(5),
				static_cast<time_type>(0.2),
				36, // magazine size
				static_cast<time_type>(4) // reload time
				
			)
		);
	case weapon_type::shotgun:
		return auto_ptr(
			new shotgun(
				env,
				type,
				static_cast<time_type>(1), // cooldown
				static_cast<space_unit>(0.2), // spread radius
				10, // shells
				static_cast<space_unit>(1), // damage,
				8, // magazine size
				static_cast<time_type>(3) // reload time
				
			)
		);
	case weapon_type::rocket_launcher:
		return auto_ptr(
			new rocket_launcher(
				env,
				type,
				static_cast<time_type>(0.8), // cooldown
				static_cast<space_unit>(9), // damage
				static_cast<space_unit>(120), // aoe
				1, // magazine size
				static_cast<time_type>(1.8) // reload time
				
			)
		);
	case weapon_type::grenade:
		return auto_ptr(
			new grenade(
				env,
				type,
				static_cast<time_type>(0.7), // cooldown
				static_cast<space_unit>(20), // damage
				static_cast<space_unit>(180), // radius
				static_cast<time_type>(0.1), // cast point
				static_cast<time_type>(1.0) // reload time
			)
		);
	case weapon_type::sentry:
		return auto_ptr(
			new sentry(
				env,
				type,
				static_cast<time_type>(5), // cooldown
				static_cast<time_type>(2), // cast point
				static_cast<time_type>(0), // reload time
				boost::phoenix::new_<
					weapons::pistol
				>(
					env,
					weapon_type::pistol,
					static_cast<time_type>(0.3), // cooldown
					static_cast<space_unit>(2), // damage
					static_cast<time_type>(0.2), // cast point
					1000,//weapon::unlimited_magazine,
					static_cast<time_type>(0) // reload time
				)
			)
		);
	default:
		throw exception(
			SGE_TEXT("Cannot create weapon for given weapon type!"));
	}
}
