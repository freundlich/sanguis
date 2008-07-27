#ifndef SANGUIS_DRAW_FACTORY_ENEMY_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_ENEMY_HPP_INCLUDED

#include "../../entity_id.hpp"
#include "../../enemy_type.hpp" 
#include "../types.hpp"
#include "types.hpp"

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_ptr enemy(
	entity_id,
	system &,
	enemy_type::type);

}
}
}

#endif
