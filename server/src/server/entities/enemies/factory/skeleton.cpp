#include <sanguis/duration_second.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/auras/burn_create.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/buffs/burn.hpp>
#include <sanguis/server/buffs/burn_interval.hpp>
#include <sanguis/server/buffs/define_special.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/normal.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/factory/make.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/skeleton.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::skeleton(
	sanguis::server::entities::enemies::factory::parameters const &_parameters
)
{
	SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL(
		skeleton_burn,
		burn
	);

	return
		sanguis::server::entities::enemies::factory::make(
			_parameters,
			sanguis::server::damage::no_armor(),
			sanguis::server::health(
				12.f
				*
				std::sqrt(
					_parameters.difficulty().get()
				)
			),
			sanguis::server::entities::movement_speed(
				50.f
			),
			sanguis::server::ai::create_simple(
				sanguis::server::ai::sight_range(
					1000.f
				)
			),
			fcppt::make_unique_ptr<
				sanguis::server::weapons::melee
			>(
				_parameters.diff_clock(),
				_parameters.random_generator(),
				sanguis::server::weapons::range(
					100.f
				),
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						1.f
					)
				),
				sanguis::server::weapons::damage(
					10.f
				),
				sanguis::server::damage::list{
					sanguis::server::damage::normal =
						sanguis::server::damage::full
				}
			),
			sanguis::server::pickup_probability(
				0.75f
			),
			sanguis::server::exp(
				100.f
			),
			fcppt::assign::make_container<
				sanguis::server::auras::container
			>(
				sanguis::server::auras::burn_create<
					skeleton_burn
				>(
					_parameters.diff_clock(),
					sanguis::server::radius(
						300.f
					),
					sanguis::server::team::monsters,
					sanguis::server::buffs::burn_interval(
						sanguis::duration_second(
							1.f
						)
					),
					sanguis::server::damage::unit(
						1.f
						*
						std::sqrt(
							_parameters.difficulty().get()
						)
					)
				)
			).move_container()
		);
}