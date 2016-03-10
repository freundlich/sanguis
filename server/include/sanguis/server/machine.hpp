#ifndef SANGUIS_SERVER_MACHINE_HPP_INCLUDED
#define SANGUIS_SERVER_MACHINE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/io_service_fwd.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/messages/client/unique_ptr.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/net/data_buffer.hpp>
#include <sanguis/server/load.hpp>
#include <sanguis/server/machine_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/timer.hpp>
#include <sanguis/server/timer_duration.hpp>
#include <sanguis/server/states/running_fwd.hpp>
#include <alda/net/id.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/streambuf_fwd.hpp>
#include <alda/net/server/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state_machine.hpp>
#include <queue>
#include <unordered_map>
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
		alda::net::port,
		sanguis::io_service &
	);

	~machine()
	override;

	void
	listen();

	void
	send_to_all(
		sanguis::messages::server::base const &
	);

	void
	send_unicast(
		sanguis::server::player_id,
		sanguis::messages::server::base const &
	);

	bool
	process_overflow();

	sanguis::server::load const &
	resources() const;
private:
	void
	process_message(
		alda::net::id,
		sanguis::messages::client::unique_ptr &&
	);

	void
	add_overflow_message(
		alda::net::id,
		sanguis::messages::server::base const &
	);

	void
	disconnect_callback(
		alda::net::id,
		fcppt::string const &
	);

	void
	data_callback(
		alda::net::id,
		alda::net::buffer::circular_receive::streambuf &
	);

	void
	disconnect_player(
		alda::net::id
	);

	void
	data_error(
		alda::net::id,
		fcppt::string const &
	);

	void
	timer_callback();

	sanguis::server::load resources_;

	alda::net::port const port_;

	sanguis::io_service &io_service_;

	alda::net::server::object net_;

	sanguis::server::timer_duration const desired_frame_time_;

	sanguis::timer frame_timer_;

	sanguis::net::data_buffer temp_buffer_;

	typedef
	std::queue<
		sanguis::messages::server::unique_ptr
	>
	overflow_message_queue;

	typedef
	std::unordered_map<
		alda::net::id,
		overflow_message_queue
	>
	overflow_message_map;

	overflow_message_map overflow_messages_;

	sanguis::server::timer timer_;

	fcppt::signal::auto_connection const
		disconnect_connection_,
		data_connection_;
};

}
}

#endif
