#ifndef SANGUIS_SERVER_WORLD_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_MAP_HPP_INCLUDED

#include <sanguis/world_id.hpp>
#include <sanguis/server/world/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

typedef boost::ptr_map<
	sanguis::world_id,
	sanguis::server::world::object
> map;

}
}
}

#endif
