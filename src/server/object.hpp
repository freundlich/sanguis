#ifndef SANGUIS_SERVER_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_OBJECT_HPP_INCLUDED

#include "machine.hpp"
#include "object_fwd.hpp"
#include "../load/context_base_fwd.hpp"
#include "../net/port.hpp"
#include "../main_object.hpp"
#include <sge/systems/instance_fwd.hpp>
#include <sge/time/timer.hpp>
#include <fcppt/thread/object.hpp>
#include <fcppt/scoped_state_machine.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/thread/thread.hpp>

namespace sanguis
{
namespace server
{

class object
:
	public sanguis::main_object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit 
	object(
		sge::systems::instance const &,
		net::port,
		load::context_base const &
	);

	void
	quit();

	int
	run();

	bool
	running();

	~object();
private:
	void
	mainloop();

	void
	timer_callback();

	void
	reset_running();

	sge::time::timer frame_timer_;

	server::machine machine_;

	fcppt::signal::scoped_connection const timer_connection_;

	bool running_;

	boost::mutex mutex_;

	fcppt::thread::object server_thread_;

	typedef fcppt::scoped_state_machine<
		server::machine
	> scoped_machine;

	scoped_machine scoped_machine_;
};

}
}

#endif
