#ifndef SANGUIS_CREATOR_AUX__SERIALIZATION_TILE_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__SERIALIZATION_TILE_GRID_HPP_INCLUDED

#include <sanguis/creator/tile_grid.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <sge/parse/json/convert/from_enum.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assign/make_container.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace serialization
{

template<
	typename Tile
>
sge::parse::json::object
tile_grid(
	sanguis::creator::tile_grid<
		Tile
	> const &_grid
)
{
	return
		sge::parse::json::object(
			fcppt::assign::make_container<
				sge::parse::json::member_map
			>(
				sge::parse::json::member(
					FCPPT_TEXT("size"),
					sge::parse::json::convert::from_container(
						_grid.size()
					)
				)
			)(
				sge::parse::json::member(
					FCPPT_TEXT("elements"),
					sge::parse::json::array(
						fcppt::algorithm::map<
							sge::parse::json::element_vector
						>(
							_grid,
							&sge::parse::json::convert::from_enum<
								Tile
							>
						)
					)
				)
			)
		);
}

}
}
}
}

#endif