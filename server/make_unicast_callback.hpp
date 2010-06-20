#ifndef SANGUIS_SERVER_MAKE_UNICAST_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_MAKE_UNICAST_CALLBACK_HPP_INCLUDED

#include "unicast_callback.hpp"
#include "machine_fwd.hpp"

namespace sanguis
{
namespace server
{

unicast_callback const
make_unicast_callback(
	server::machine &
);

}
}

#endif
