#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_MAP_HPP_INCLUDED

#include <sanguis/server/entities/player_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <fcppt/container/map_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef fcppt::container::map<
	std::map<
		player_id,
		server::entities::player *
	>
> player_map;

}
}
}

#endif