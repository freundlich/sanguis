#ifndef SANGUIS_CREATOR_IMPL_FIND_OPPOSING_CELL_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_FIND_OPPOSING_CELL_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <fcppt/optional/object_impl.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

fcppt::optional::object<
	sanguis::creator::pos
>
find_opposing_cell(
	sanguis::creator::impl::reachable_grid const &,
	sanguis::creator::pos const &
);

}
}
}

#endif
