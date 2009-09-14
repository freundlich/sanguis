#ifndef SANGUIS_SERVER_WORLD_SIGHT_RANGE_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SIGHT_RANGE_HPP_INCLUDED

#include "sight_range_fwd.hpp"
#include "sight_range_entry_set.hpp"
#include "sight_range_entry.hpp"
#include "entity_remove_vector.hpp"
#include "../../time_type.hpp"

namespace sanguis
{
namespace server
{
namespace world
{

class sight_range {
public:
	sight_range();

	entity_remove_vector const	
	update(
		time_type
	);

	bool
	add(
		entity_id,
		time_type
	);

	bool
	contains(
		entity_id
	) const;
private:
	sight_range_entry_set entries_;
};

}
}
}

#endif
