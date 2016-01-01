#ifndef SANGUIS_SERVER_OPTIONAL_ANGLE_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_OPTIONAL_ANGLE_FWD_HPP_INCLUDED

#include <sanguis/server/angle_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace server
{

typedef
fcppt::optional::object<
	sanguis::server::angle
>
optional_angle;

}
}

#endif
