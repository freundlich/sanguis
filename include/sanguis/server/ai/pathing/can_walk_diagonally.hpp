#ifndef SANGUIS_SERVER_AI_PATHING_CAN_WALK_DIAGONALLY_HPP_INCLUDED
#define SANGUIS_SERVER_AI_PATHING_CAN_WALK_DIAGONALLY_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace pathing
{

bool
can_walk_diagonally(
	sanguis::creator::grid const &,
	sanguis::creator::pos,
	sanguis::creator::pos
);

}
}
}
}

#endif
