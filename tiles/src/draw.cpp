#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/tiles/cell_container.hpp>
#include <sanguis/tiles/collection_fwd.hpp>
#include <sanguis/tiles/draw.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/lower_bound.hpp>
#include <sanguis/tiles/upper_bound.hpp>
#include <sanguis/tiles/impl/draw_connecting.hpp>
#include <sanguis/tiles/impl/draw_non_connecting.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/container/grid/clamp_pos.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/dim.hpp>


sanguis::tiles::cell_container
sanguis::tiles::draw(
	sanguis::creator::grid const &_foreground,
	sanguis::creator::background_grid const &_background,
	sanguis::tiles::collection &_collection,
	sanguis::tiles::lower_bound const _lower_bound,
	sanguis::tiles::upper_bound const _upper_bound
)
{
	FCPPT_ASSERT_PRE(
		_foreground.size()
		==
		_background.size()
	);

	sanguis::creator::grid::dim const min_size{
		fcppt::math::dim::fill<
			sanguis::creator::grid::dim
		>(
			1u
		)
	};

	if(
		_foreground.size()
		<=
		min_size
	)
		return
			sanguis::tiles::cell_container();

	sanguis::tiles::lower_bound const lower_bound(
		fcppt::container::grid::clamp_pos(
			_lower_bound.get(),
			_foreground.size()
		)
	);

	sanguis::tiles::lower_bound const connecting_lower_bound(
		fcppt::container::grid::clamp_pos(
			_lower_bound.get()
			+
			min_size
			,
			_foreground.size()
		)
	);

	sanguis::tiles::upper_bound const upper_bound(
		fcppt::container::grid::clamp_pos(
			_upper_bound.get()
			,
			_foreground.size()
		)
	);

	return
		fcppt::algorithm::join(
			sanguis::tiles::impl::draw_connecting(
				_collection,
				sanguis::tiles::error::missing_background,
				_background,
				connecting_lower_bound,
				upper_bound
			),
			sanguis::tiles::impl::draw_connecting(
				_collection,
				sanguis::tiles::error::missing_foreground,
				_foreground,
				connecting_lower_bound,
				upper_bound
			),
			sanguis::tiles::impl::draw_non_connecting(
				_collection,
				sanguis::tiles::error::missing_object,
				_foreground,
				lower_bound,
				upper_bound
			)
		);
}
