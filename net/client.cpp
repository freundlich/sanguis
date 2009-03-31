#include "detail/client_impl.hpp"

sanguis::net::client::client() 
	: impl_(new detail::client_impl())
{
}

void sanguis::net::client::connect(
	hostname_type const &s,
	port_type const port)
{
	return impl_->connect(s,port);
}

void sanguis::net::client::queue(
	data_type const &data)
{
	return impl_->queue(data);
}

void sanguis::net::client::process()
{
	return impl_->process();
}

sge::signal::auto_connection sanguis::net::client::register_connect(connect_function const &f)
{
	return impl_->register_connect(f);
}

sge::signal::auto_connection sanguis::net::client::register_disconnect(disconnect_function const &f)
{
	return impl_->register_disconnect(f);
}

sge::signal::auto_connection sanguis::net::client::register_data(data_function const &f)
{
	return impl_->register_data(f);
}

sanguis::net::client::~client() {}
