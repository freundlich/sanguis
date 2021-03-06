#ifndef SANGUIS_SERVER_PERKS_TREE_REQUIRED_PARENT_LEVEL_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_REQUIRED_PARENT_LEVEL_HPP_INCLUDED

#include <sanguis/server/level.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::level::value_type,
	required_parent_level
);

}
}
}
}

#endif
