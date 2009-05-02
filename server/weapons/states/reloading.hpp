#ifndef SANGUIS_SERVER_WEAPONS_STATES_RELOADING_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_RELOADING_HPP_INCLUDED

#include "reloading_fwd.hpp"
#include "../weapon.hpp"
#include "../events/poll_fwd.hpp"
#include "../../../diff_clock.hpp"
#include <sge/time/timer.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace states
{

class reloading
: public
	boost::statechart::state<
		reloading,
		weapon
	>
{
public:
	typedef boost::statechart::custom_reaction<
		events::poll
	> reactions;

	explicit reloading(
		my_context);
	
	boost::statechart::result
	react(
		events::poll const &);
private:
	diff_clock diff_clock_;
	sge::time::timer reload_time;
};

}
}
}
}

#endif
