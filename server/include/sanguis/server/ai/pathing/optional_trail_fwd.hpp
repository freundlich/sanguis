#ifndef SANGUIS_SERVER_AI_PATHING_OPTIONAL_TRAIL_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_AI_PATHING_OPTIONAL_TRAIL_FWD_HPP_INCLUDED

#include <sanguis/server/ai/pathing/trail.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace pathing
{

typedef
fcppt::optional<
	sanguis::server::ai::pathing::trail
>
optional_trail;

}
}
}
}

#endif