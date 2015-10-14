#ifndef SANGUIS_TILES_CELL_HPP_INCLUDED
#define SANGUIS_TILES_CELL_HPP_INCLUDED

#include <sanguis/tiles/cell_fwd.hpp>
#include <sanguis/tiles/content.hpp>
#include <sanguis/tiles/is_background.hpp>
#include <sanguis/tiles/path_reference.hpp>
#include <sanguis/tiles/pos.hpp>
#include <sanguis/tiles/symbol.hpp>


namespace sanguis
{
namespace tiles
{

class cell
{
public:
	cell(
		sanguis::tiles::pos,
		sanguis::tiles::content const &,
		sanguis::tiles::path_reference,
		sanguis::tiles::is_background
	);

	SANGUIS_TILES_SYMBOL
	sanguis::tiles::pos
	pos() const;

	SANGUIS_TILES_SYMBOL
	sanguis::tiles::content const &
	content() const;

	SANGUIS_TILES_SYMBOL
	sanguis::tiles::path_reference
	path() const;

	SANGUIS_TILES_SYMBOL
	sanguis::tiles::is_background
	is_background() const;
private:
	sanguis::tiles::pos pos_;

	sanguis::tiles::content content_;

	sanguis::tiles::path_reference path_;

	sanguis::tiles::is_background is_background_;
};

}
}

#endif
