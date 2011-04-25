#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_EXPLOSION_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_EXPLOSION_CALLBACK_HPP_INCLUDED

#include "base_ptr.hpp"
#include "particle_type.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

typedef fcppt::function::object<
	particle::base_ptr (
		particle::particle_type::type
	)
> explosion_callback;

}
}
}
}

#endif
