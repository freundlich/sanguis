#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/aux_/result.hpp>


sanguis::creator::aux_::result::result(
	sanguis::creator::grid const &_grid,
	sanguis::creator::background_grid const &_background_grid,
	sanguis::creator::opening_container const &_openings,
	sanguis::creator::spawn_container const &_spawns,
	sanguis::creator::destructible_container const &_destructibles
)
:
	grid_(
		_grid
	),
	background_grid_(
		_background_grid
	),
	openings_(
		_openings
	),
	spawns_(
		_spawns
	),
	destructibles_(
		_destructibles
	)
{
}

sanguis::creator::grid const &
sanguis::creator::aux_::result::grid() const
{
	return
		grid_;
}

sanguis::creator::background_grid const &
sanguis::creator::aux_::result::background_grid() const
{
	return
		background_grid_;
}

sanguis::creator::opening_container const &
sanguis::creator::aux_::result::openings() const
{
	return
		openings_;
}

sanguis::creator::spawn_container const &
sanguis::creator::aux_::result::spawns() const
{
	return
		spawns_;
}

sanguis::creator::destructible_container const &
sanguis::creator::aux_::result::destructibles() const
{
	return
		destructibles_;
}
