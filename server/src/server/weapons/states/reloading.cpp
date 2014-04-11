#include <sanguis/diff_timer.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/reload.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/castpoint.hpp>
#include <sanguis/server/weapons/states/idle.hpp>
#include <sanguis/server/weapons/states/reloading.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::weapons::states::reloading::reloading(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	reload_time_(
		sanguis::diff_timer::parameters(
			this->context<
				sanguis::server::weapons::weapon
			>().diff_clock(),
			this->context<
				sanguis::server::weapons::weapon
			>().reload_time()->get()
			/
			this->context<
				sanguis::server::weapons::weapon
			>().owner().irs().get()
		)
	),
	cancelled_(
		true
	)
{
	this->context<
		sanguis::server::weapons::weapon
	>().weapon_status(
		sanguis::weapon_status::reloading
	);
}

FCPPT_PP_POP_WARNING

sanguis::server::weapons::states::reloading::~reloading()
{
}

boost::statechart::result
sanguis::server::weapons::states::reloading::react(
	sanguis::server::weapons::events::poll const &
)
{
	if(
		!reload_time_.expired()
	)
		return
			this->discard_event();

	this->context<
		sanguis::server::weapons::weapon
	>().reset_magazine();

	return
		cancelled_
		||
		!this->context<
			sanguis::server::weapons::weapon
		>().usable()
		?
			this->transit<
				sanguis::server::weapons::states::idle
			>()
		:
			this->transit<
				sanguis::server::weapons::states::castpoint
			>()
		;
}

boost::statechart::result
sanguis::server::weapons::states::reloading::react(
	sanguis::server::weapons::events::shoot const &
)
{
	cancelled_ = false;

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::weapons::states::reloading::react(
	sanguis::server::weapons::events::stop const &
)
{
	cancelled_ = true;

	return
		this->discard_event();
}