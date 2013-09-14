#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/aux_/deserialization/background_grid.hpp>
#include <sanguis/creator/aux_/deserialization/tile_grid.hpp>
#include <sge/parse/json/object.hpp>


sanguis::creator::background_grid
sanguis::creator::aux_::deserialization::background_grid(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::creator::aux_::deserialization::tile_grid<
			sanguis::creator::background_grid
		>(
			_object
		);
}
