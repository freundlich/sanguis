#ifndef SANGUIS_CLIENT_LOAD_TILES_ORIENTATION_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_ORIENTATION_FWD_HPP_INCLUDED

#include <sanguis/client/load/tiles/direction.hpp>
#include <fcppt/container/bitfield/object_from_enum.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace tiles
{

typedef
fcppt::container::bitfield::object_from_enum<
	sanguis::client::load::tiles::direction
>
orientation;

}
}
}
}

#endif
