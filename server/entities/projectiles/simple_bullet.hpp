#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED

#include "projectile.hpp"
#include "../with_health_fwd.hpp"
#include "../../environment/load_context_ptr.hpp"
#include "../../damage/unit.hpp"
#include "../../team.hpp"
#include "../../space_unit.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class simple_bullet
:
	public projectile
{
public:
	simple_bullet(
		server::environment::load_context_ptr,
		team::type,
		damage::unit,
		space_unit direction
	);
private:
	void
	do_damage(
		with_health &
	);
	
	damage::unit const damage_;
};

}
}
}
}

#endif
