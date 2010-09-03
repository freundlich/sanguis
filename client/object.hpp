#ifndef SANGUIS_CLIENT_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_OBJECT_HPP_INCLUDED

#include "machine.hpp"
#include "config/settings/object.hpp"
#include "config/settings/saver.hpp"
#include "../load/context.hpp"
#include "../net/port_type.hpp"
#include "../server/object_fwd.hpp"
#include "../main_object.hpp"
#include "../scoped_machine.hpp"

#include <sge/audio/pool.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/font/drawer_ptr.hpp>
#include <sge/font/metrics_ptr.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/mainloop/io_service_ptr.hpp>
#include <sge/time/timer.hpp>
#include <sge/systems/instance_fwd.hpp>

#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace client
{

class object
:
	public main_object
{
	FCPPT_NONCOPYABLE(object)
public:
	explicit object(
		sge::systems::instance &,
		boost::program_options::variables_map const &
	);

	~object();
private:
	int
	run();

	void
	register_handler();

	void
	loop_handler();

	void
	create_server(
		net::port_type
	);

	int
	quit_server();

	// declare the config stuff first, so they are destroyed last
	config::settings::object settings_;

	config::settings::saver saver_;

	sge::systems::instance &sys_;

	sge::input::key_state_tracker key_state_tracker_;
	
	sge::font::metrics_ptr const font_metrics_;

	sge::font::drawer_ptr const font_drawer_;

	sge::console::object console_;

	sge::console::gfx console_gfx_;

	sge::audio::pool sound_pool_;

	sge::mainloop::io_service_ptr const io_service_;

	load::context resources_;

	client::machine machine_;

	sge::time::timer frame_timer_;

	fcppt::scoped_ptr<
		server::object
	> server_;

	bool running_;

	bool next_handler_;

	typedef sanguis::scoped_machine<
		client::machine
	> scoped_machine;

	scoped_machine scoped_machine_;
};

}
}

#endif