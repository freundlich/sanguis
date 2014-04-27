#ifndef SANGUIS_SERVER_AI_ANGLE_TO_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_ANGLE_TO_TARGET_HPP_INCLUDED

#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/optional_angle_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

sanguis::server::optional_angle const
angle_to_target(
	sanguis::server::entities::with_ai &,
	sanguis::server::center
);

}
}
}

#endif