#ifndef SANGUIS_SERVER_WEAPONS_MELEE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MELEE_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee_parameters_fwd.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class melee_parameters
{
	FCPPT_NONASSIGNABLE(
		melee_parameters
	);
public:
	melee_parameters(
		sanguis::server::weapons::range,
		sanguis::server::weapons::backswing_time,
		sanguis::server::weapons::damage,
		sanguis::server::damage::array const &
	);

	sanguis::server::weapons::backswing_time const
	backswing_time() const;

	sanguis::server::weapons::attributes::damage const
	damage() const;

	sanguis::server::weapons::range const
	range() const;

	sanguis::server::damage::array const &
	damage_values() const;

	void
	extra_damage(
		sanguis::server::weapons::damage
	);
private:
	sanguis::server::weapons::range const range_;

	sanguis::server::weapons::backswing_time const backswing_time_;

	sanguis::server::weapons::attributes::damage damage_;

	sanguis::server::damage::array const damage_values_;
};

}
}
}

#endif