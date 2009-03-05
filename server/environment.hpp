#ifndef SANGUIS_SERVER_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_HPP_INCLUDED

#include "send_callback.hpp"
#include "insert_callback.hpp"
#include "exp_callback.hpp"
#include "level_callback.hpp"
#include "load_callback.hpp"
#include <sge/collision/world_fwd.hpp>

namespace sanguis
{
namespace server
{
struct environment
{
	send_callback send;
	insert_callback insert;
	exp_callback exp;
	level_callback level;
	load_callback load;
	sge::collision::world_ptr const collision;

	environment(
		send_callback const &,
		insert_callback const &,
		exp_callback const &,
		level_callback const &,
		load_callback const &,
		sge::collision::world_ptr);
};
}
}

#endif
