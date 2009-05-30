#ifndef SANGUIS_SERVER_WEAPONS_STATES_CASTPOINT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_CASTPOINT_HPP_INCLUDED

#include "castpoint_fwd.hpp"
#include "../weapon.hpp"
#include "../events/poll_fwd.hpp"
#include "../events/shoot_fwd.hpp"
#include "../events/stop_fwd.hpp"
#include "../../pos_type.hpp"
#include "../../../diff_clock.hpp"
#include <sge/time/timer.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/optional_decl.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace states
{

class castpoint
: public
	boost::statechart::state<
		castpoint,
		weapon
	>
{
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::shoot
		>,
		boost::statechart::custom_reaction<
			events::poll
		>,
		boost::statechart::custom_reaction<
			events::stop
		>
	> reactions;

	explicit castpoint(
		my_context);

	boost::statechart::result
	react(
		events::shoot const &);
	
	boost::statechart::result
	react(
		events::poll const &);

	boost::statechart::result
	react(
		events::stop const &);
private:
	diff_clock diff_clock_;
	sge::time::timer attack_time;
	sge::optional<
		pos_type
	> attack_dest;
};

}
}
}
}

#endif
