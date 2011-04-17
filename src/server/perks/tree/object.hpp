#ifndef SANGUIS_SERVER_PERKS_TREE_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_OBJECT_HPP_INCLUDED

#include "status_fwd.hpp"
#include <fcppt/container/tree/object_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

typedef fcppt::container::tree::object<
	status
> object;

}
}
}
}

#endif
