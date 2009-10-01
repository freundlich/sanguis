#ifndef SANGUIS_SERVER_COLLISION_EXECUTE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_EXECUTE_FUNCTION_HPP_INCLUDED

#include "base_fwd.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

typedef sge::function::object<
	void (
		collision::base &,
		collision::base &
	)
> execute_function;

}
}
}

#endif
