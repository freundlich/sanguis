#ifndef SANGUIS_SERVER_COLLISION_BODY_EXIT_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_EXIT_CALLBACK_HPP_INCLUDED

#include "body_base_fwd.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

typedef fcppt::function::object<
	void(
		collision::body_base &
	)
> body_exit_callback;

}
}
}

#endif
