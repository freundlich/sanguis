#ifndef SANGUIS_NET_SERVER_DATA_FUNCTION_HPP_INCLUDED
#define SANGUIS_NET_SERVER_DATA_FUNCTION_HPP_INCLUDED

#include "../id.hpp"
#include "../receive_buffer.hpp"

namespace sanguis
{
namespace net
{
namespace server
{

typedef void
data_function(
	net::id,
	net::receive_buffer &
);

}
}
}

#endif