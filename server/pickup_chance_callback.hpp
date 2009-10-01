#ifndef SANGUIS_SERVER_PICKUP_CHANCE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_PICKUP_CHANCE_CALLBACK_HPP_INCLUDED

#include "probability_type.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef sge::function::object<
	bool (
		probability_type
	)
> pickup_chance_callback;

}
}

#endif
