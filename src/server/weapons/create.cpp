#include "create.hpp"
#include "pistol.hpp"
#include "shotgun.hpp"
#include "rocket_launcher.hpp"
#include "weapon.hpp"
#include "grenade.hpp"
#include "sentry.hpp"
#include "unlimited_magazine_size.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>

sanguis::server::weapons::unique_ptr
sanguis::server::weapons::create(
	weapon_type::type const _type
)
{
	switch(
		_type
	)
	{
	case weapon_type::melee:
		throw sanguis::exception(
			FCPPT_TEXT("Please create melee weapons directly, not through the weapon factory!")
		);
	case weapon_type::pistol:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					pistol
				>(
					_type,
					base_cooldown(0.5f),
					damage(5),
					cast_point(0.2f),
					magazine_size(18),
					reload_time(2.f),
					range(1000)
				)
			);
	case weapon_type::dual_pistol:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					pistol
				>(
					_type,
					base_cooldown(0.33f),
					damage(5),
					cast_point(0.2f),
					magazine_size(36),
					reload_time(4.f),
					range(1000)
				)
			);
	case weapon_type::shotgun:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					shotgun
				>(
					_type,
					base_cooldown(1.f),
					static_cast<space_unit>(0.2), // spread radius
					10u, // shells
					damage(1),
					magazine_size(8),
					reload_time(3.f)
				)
			);
	case weapon_type::rocket_launcher:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					rocket_launcher
				>(
					_type,
					base_cooldown(0.8f),
					damage(9),
					aoe(120), 
					magazine_size(1),
					reload_time(1.8f)
				)
			);
	case weapon_type::grenade:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					grenade
				>(
					_type,
					base_cooldown(0.7f),
					damage(20),
					aoe(180),
					cast_point(0.1f),
					reload_time(1.f)
				)
			);
	case weapon_type::sentry:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					sentry
				>(
					_type,
					base_cooldown(5.f),
					cast_point(2.f),
					reload_time(0.f),
					boost::phoenix::new_<
						weapons::pistol
					>(
						weapon_type::pistol,
						base_cooldown(0.3f),
						damage(2),
						cast_point(0.2f),
						unlimited_magazine_size,
						reload_time(0.f),
						range(1000)
					)
				)
			);
	case weapon_type::none:
	case weapon_type::size:
		break;
	}

	throw sanguis::exception(
		FCPPT_TEXT("Cannot create weapon for given weapon type!")
	);
}
