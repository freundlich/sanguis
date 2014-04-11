#include <sanguis/duration_second.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/pistol_parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/dual_pistols.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::factory::dual_pistols(
	sanguis::server::weapons::factory::parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::weapons::pistol
		>(
			_parameters.diff_clock(),
			_parameters.random_generator(),
			_parameters.weapon_type(),
			sanguis::server::weapons::pistol_parameters(
				sanguis::server::weapons::accuracy(
					0.75f
				),
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						0.33f
					)
				),
				sanguis::server::weapons::damage(
					5.f
				),
				sanguis::server::weapons::cast_point(
					sanguis::duration_second(
						0.2f
					)
				),
				sanguis::server::weapons::magazine_size(
					36u
				),
				sanguis::server::weapons::reload_time(
					sanguis::duration_second(
						4.f
					)
				),
				sanguis::server::weapons::range(
					1000.f
				)
			)
		);
}