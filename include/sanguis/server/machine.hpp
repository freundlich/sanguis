#ifndef SANGUIS_SERVER_MACHINE_HPP_INCLUDED
#define SANGUIS_SERVER_MACHINE_HPP_INCLUDED

#include <sanguis/io_service_fwd.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/load/context_base_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/net/data_buffer.hpp>
#include <sanguis/server/machine_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/timer.hpp>
#include <sanguis/server/states/running_fwd.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <alda/net/id.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <alda/net/server/object.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state_machine.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

struct machine
:
	public boost::statechart::state_machine<
		sanguis::server::machine,
		sanguis::server::states::running
	>
{
	FCPPT_NONCOPYABLE(
		machine
	);
public:
	machine(
		sanguis::load::context_base const &,
		sge::charconv::system &,
		alda::net::port,
		sanguis::io_service &
	);

	~machine();

	void
	listen();

	void
	stop();

	void
	send_to_all(
		sanguis::messages::base const &
	);

	void
	send_unicast(
		sanguis::server::player_id,
		sanguis::messages::base const &
	);

	sanguis::load::context_base const &
	resources() const;

	sge::charconv::system &
	charconv_system() const;
private:
	void
	process_message(
		alda::net::id,
		sanguis::messages::auto_ptr
	);

	void
	connect_callback(
		alda::net::id
	);

	void
	disconnect_callback(
		alda::net::id,
		fcppt::string const &
	);

	void
	data_callback(
		alda::net::id,
		alda::net::buffer::circular_receive::object &
	);

	void
	timer_callback();

	load::context_base const &resources_;

	sge::charconv::system &charconv_system_;

	alda::net::port const port_;

	sanguis::io_service &io_service_;

	alda::net::server::object net_;

	sanguis::timer frame_timer_;

	sanguis::net::data_buffer temp_buffer_;

	fcppt::signal::scoped_connection const
		s_conn_,
		s_disconn_,
		s_data_;

	sanguis::server::timer timer_;
};

}
}

#endif
