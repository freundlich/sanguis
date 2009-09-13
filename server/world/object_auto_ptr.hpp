#ifndef SANGUIS_SERVER_WORLD_OBJECT_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_AUTO_PTR_HPP_INCLUDED

#include "object_fwd.hpp"
#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

typedef sge::auto_ptr<
	object
> object_auto_ptr;

}
}
}

#endif
