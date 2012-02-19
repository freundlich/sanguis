#ifndef SANGUIS_SERVER_WEAPONS_STATES_READY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_READY_HPP_INCLUDED

#include <sanguis/server/weapons/states/ready_fwd.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/shoot_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace states
{

class ready
:
	public boost::statechart::simple_state<
		ready,
		weapon
	>
{
	FCPPT_NONCOPYABLE(
		ready
	);
public:
	typedef boost::mpl::list1<
		boost::statechart::custom_reaction<
			events::shoot
		>
	> reactions;

	ready();

	virtual ~ready();

	boost::statechart::result
	react(
		events::shoot const &
	);
};

}
}
}
}

#endif