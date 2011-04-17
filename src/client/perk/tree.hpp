#ifndef SANGUIS_CLIENT_PERK_TREE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_TREE_HPP_INCLUDED

#include "../../perk_type.hpp"
#include <fcppt/container/tree/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace perk
{

typedef fcppt::container::tree::object<
	sanguis::perk_type::type
> tree;

}
}
}

#endif
