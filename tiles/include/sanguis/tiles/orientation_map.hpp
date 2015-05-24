#ifndef SANGUIS_TILES_ORIENTATION_MAP_HPP_INCLUDED
#define SANGUIS_TILES_ORIENTATION_MAP_HPP_INCLUDED

#include <sanguis/tiles/area_container.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <fcppt/container/bitfield/std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tiles
{

typedef
std::unordered_map<
	sanguis::tiles::orientation,
	sanguis::tiles::area_container
>
orientation_map;

}
}

#endif