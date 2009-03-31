#ifndef NET_CLIENT_HPP_INCLUDED
#define NET_CLIENT_HPP_INCLUDED

#include "output_buffer.hpp"
#include "hostname_type.hpp"
#include "port_type.hpp"
#include "data_type.hpp"

#include <sge/signal/object.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/scoped_ptr.hpp>
#include <sge/noncopyable.hpp>

#include <boost/function.hpp>

namespace sanguis
{
namespace net
{
namespace detail
{
class client_impl;
}

class client
{
SGE_NONCOPYABLE(client)
public:
	typedef void connect_fun ();
	typedef void disconnect_fun (sge::string const &);
	typedef void data_fun (data_type const &);
	typedef boost::function<connect_fun> connect_function;
	typedef boost::function<disconnect_fun> disconnect_function;
	typedef boost::function<data_fun> data_function;

	client();
	void connect(
		hostname_type const &,
		port_type);
	void queue(
		data_type const &);
	void process();
	sge::signal::auto_connection register_connect(
		connect_function const &);
	sge::signal::auto_connection register_disconnect(
		disconnect_function const &);
	sge::signal::auto_connection register_data(
		data_function const &);
	~client();
private:
	sge::scoped_ptr<detail::client_impl> impl_;
};
}
}

#endif
