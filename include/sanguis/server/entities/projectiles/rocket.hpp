#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_ROCKET_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_ROCKET_HPP_INCLUDED

#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class rocket
:
	public aoe_projectile
{
	FCPPT_NONCOPYABLE(
		rocket
	);
public:
	rocket(
		sanguis::diff_clock const &,
		server::environment::load_context &,
		server::team::type team,
		damage::unit,
		server::radius aoe,
		server::direction
	);

	~rocket();
private:
	void
	do_damage(
		with_health &
	);

	void
	on_remove();

	sanguis::diff_clock const &diff_clock_;

	damage::unit const damage_;
};

}
}
}
}

#endif