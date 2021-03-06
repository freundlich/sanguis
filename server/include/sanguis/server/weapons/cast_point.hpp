#ifndef SANGUIS_SERVER_WEAPONS_CAST_POINT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CAST_POINT_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::duration,
	cast_point
);

}
}
}

#endif
