#ifndef SANGUIS_SERVER_COLLISION_TO_SGE_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_TO_SGE_DIM_HPP_INCLUDED

#include <sanguis/server/dim.hpp>
#include <sge/projectile/dim2.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

sge::projectile::dim2 const
to_sge_dim(
	server::dim const &
);

}
}
}

#endif