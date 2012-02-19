#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_GEN_LIFE_TIME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_GEN_LIFE_TIME_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::duration,
	gen_life_time
);

}
}
}
}

#endif