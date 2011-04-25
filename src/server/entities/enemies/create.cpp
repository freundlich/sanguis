#include "create.hpp"
#include "enemy.hpp"
#include "../../damage/no_armor.hpp"
#include "../../damage/list.hpp"
#include "../../weapons/melee.hpp"
#include "../../weapons/pistol.hpp"
#include "../../weapons/unique_ptr.hpp"
#include "../../ai/create_simple.hpp"
#include "../../../exception.hpp"
#include "../../../time_from_second.hpp"
#include <fcppt/container/map_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::create(
	enemy_type::type const _etype,
	environment::load_context &_load_context,
	entities::auto_weak_link const _spawn
)
{
	switch(
		_etype
	)
	{
	case enemy_type::zombie00:
		return entities::unique_ptr(
			new enemy(
//			fcppt::make_unique_ptr<
//				enemy
//			>(
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(9),
				movement_speed(25),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::pistol
					>(
						weapon_type::pistol,
						weapons::base_cooldown(
							sanguis::time_from_second(
								1.f
							)
						),
						weapons::damage(1),
						weapons::cast_point(
							sanguis::time_from_second(
								0
							)
						),
						weapons::magazine_size(3),
						weapons::reload_time(
							sanguis::time_from_second(
								15.f
							)
						),
						weapons::range(1000)
					)
				),
				server::probability(0.25f),
				server::exp(10),
				_spawn
			)
		);
	case enemy_type::zombie01:
		return unique_ptr(
			new enemy(
//			fcppt::make_unique_ptr<
//				enemy
//			>(
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(3),
				movement_speed(20),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						weapons::range(75),
						weapons::base_cooldown(
							sanguis::time_from_second(
								2.f
							)
						),
						weapons::damage(2)
					)
				),
				server::probability(0.25f),
				server::exp(5),
				_spawn
			)
		);
	case enemy_type::wolf_black:
	case enemy_type::wolf_brown:
	case enemy_type::wolf_white:
		return unique_ptr(
			new enemy(
			//fcppt::make_unique_ptr<
			//	enemy
			//>(
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(3),
				movement_speed(85),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						weapons::range(75),
						weapons::base_cooldown(
							sanguis::time_from_second(
								1.f
							)
						),
						weapons::damage(4)
					)
				),
				server::probability(0.25f),
				server::exp(10),
				_spawn
			)
		);
	case enemy_type::skeleton:
		return unique_ptr(
			new enemy(
			//fcppt::make_unique_ptr<
			//	enemy
			//>(
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(500),
				movement_speed(50),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						weapons::range(100),
						weapons::base_cooldown(
							sanguis::time_from_second(
								1.f
							)
						),
						weapons::damage(10)
					)
				),
				server::probability(0.75f),
				server::exp(300),
				_spawn
			)
		);
	case enemy_type::maggot:
		return unique_ptr(
			new enemy(
			//fcppt::make_unique_ptr<
			//	enemy
			//>(
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(1),
				movement_speed(40),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						weapons::range(75),
						weapons::base_cooldown(
							sanguis::time_from_second(
								1.f
							)
						),
						weapons::damage(0.5f)
					)
				),
				server::probability(0.1f),
				server::exp(1),
				_spawn
			)
		);
	case enemy_type::spider:
		return unique_ptr(
			new enemy(
			//fcppt::make_unique_ptr<
			//	enemy
			//>(
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(12),
				movement_speed(75),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						weapons::range(75),
						weapons::base_cooldown(
							sanguis::time_from_second(
								2.f
							)
						),
						weapons::damage(5)
					)
				),
				server::probability(0.5f),
				server::exp(12),
				_spawn
			)		
		);
	case enemy_type::size:
		break;
	}

	throw exception(
		FCPPT_TEXT("Invalid enemy_type in factory!")
	);
}
