#include "io_service_wrapper.hpp"

boost::asio::io_service &net::io_service_wrapper()
{
	static boost::asio::io_service io;
	return io;
}
