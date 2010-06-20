#ifndef SANGUIS_SERVER_MAKE_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_MAKE_SEND_CALLBACK_HPP_INCLUDED

#include "send_callback.hpp"
#include "machine_fwd.hpp"

namespace sanguis
{
namespace server
{

send_callback const
make_send_callback(
	server::machine &
);

}
}

#endif
