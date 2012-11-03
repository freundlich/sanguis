#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/vector_fwd.hpp>
#include <sanguis/server/collision/distance.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/log_location.hpp>
#include <sanguis/server/weapons/magazine_count.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/unlimited_magazine_count.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/reset.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/ready.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/text.hpp>


namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::server::weapons::log_location()
		/
		FCPPT_TEXT("weapon")
	)
);

}

sanguis::server::weapons::weapon::weapon(
	sanguis::diff_clock const &_diff_clock,
	sanguis::weapon_type::type const _type,
	sanguis::server::weapons::range const _range,
	sanguis::server::weapons::magazine_size const _magazine_size,
	sanguis::server::weapons::magazine_count const _magazine_count,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::reload_time const _reload_time
)
:
	diff_clock_(
		_diff_clock
	),
	type_(
		_type
	),
	range_(
		_range
	),
	magazine_used_(
		0u
	),
	magazine_count_(
		_magazine_count.get()
	),
	magazine_size_(
		_magazine_size
	),
	cast_point_(
		_cast_point
	),
	backswing_time_(
		_base_cooldown.get()
		-
		_cast_point.get()
	),
	reload_time_(
		_reload_time.get()
	),
	ias_(
		0.f
	),
	irs_(
		0.f
	)
{
	if(
		_cast_point.get() > _base_cooldown.get()
	)
		FCPPT_LOG_WARNING(
			::logger,
			fcppt::log::_
				<< FCPPT_TEXT("A weapon's cast point interval is bigger than its cooldown!")
	);

	FCPPT_ASSERT_PRE(
		this->magazine_size().get() != 0
	);

	// TODO: use a scoped state machine!
	this->initiate();
}


sanguis::server::weapons::range const
sanguis::server::weapons::weapon::range() const
{
	return range_;
}

sanguis::weapon_type::type
sanguis::server::weapons::weapon::type() const
{
	return type_;
}

void
sanguis::server::weapons::weapon::update(
	sanguis::server::entities::with_weapon &_owner
)
{
	if(
		!this->usable()
	)
		return;

	this->process_event(
		sanguis::server::weapons::events::poll(
			_owner
		)
	);
}

void
sanguis::server::weapons::weapon::attack(
	sanguis::server::entities::with_weapon &_from,
	sanguis::server::vector const &_to
)
{
	if(
		!this->usable()
	)
		return;

	this->process_event(
		events::shoot(
			_from,
			_to
		)
	);
}

void
sanguis::server::weapons::weapon::stop()
{
	this->process_event(
		events::stop()
	);
}

void
sanguis::server::weapons::weapon::repickup()
{
	this->reset_magazine();

	this->process_event(
		events::reset()
	);

	if(
		magazine_count_ != unlimited_magazine_count.get()
	)
		++magazine_count_;
}

sanguis::server::weapons::magazine_size const
sanguis::server::weapons::weapon::magazine_size() const
{
	return magazine_size_;
}

bool
sanguis::server::weapons::weapon::in_range(
	sanguis::server::entities::base const &_from,
	sanguis::server::vector const &_to
) const
{
	return
		sanguis::server::collision::distance(
			_from,
			_to
		)
		< this->range().get();
}

void
sanguis::server::weapons::weapon::attack_speed(
	sanguis::time_unit const _ias
)
{
	ias_ = _ias;
}

void
sanguis::server::weapons::weapon::reload_speed(
	sanguis::time_unit const _irs
)
{
	irs_ = _irs;
}

sanguis::server::weapons::weapon::~weapon()
{
	this->terminate(); // FIXME!
}

bool
sanguis::server::weapons::weapon::usable() const
{
	return magazine_count_ > 0;
}

sanguis::diff_clock const &
sanguis::server::weapons::weapon::diff_clock() const
{
	return diff_clock_;
}

void
sanguis::server::weapons::weapon::reset_magazine()
{
	magazine_used_ = 0;
}

void
sanguis::server::weapons::weapon::use_magazine_item()
{
	++magazine_used_;

	FCPPT_ASSERT_ERROR(
		magazine_used_ <= magazine_size_.get()
	);
}

bool
sanguis::server::weapons::weapon::magazine_empty() const
{
	return
		magazine_used_ == magazine_size_.get();
}

void
sanguis::server::weapons::weapon::magazine_exhausted()
{
	if(
		magazine_count_ != unlimited_magazine_count.get()
	)
		--magazine_count_;
}

sanguis::server::weapons::cast_point const
sanguis::server::weapons::weapon::cast_point() const
{
	return
		sanguis::server::weapons::cast_point(
			cast_point_.get() / ias_
		);
}

sanguis::server::weapons::backswing_time const
sanguis::server::weapons::weapon::backswing_time() const
{
	return
		sanguis::server::weapons::backswing_time(
			backswing_time_.get() / ias_
		);
}

sanguis::server::weapons::reload_time const
sanguis::server::weapons::weapon::reload_time() const
{
	return
		sanguis::server::weapons::reload_time(
			reload_time_.get() / irs_
		);
}

void
sanguis::server::weapons::weapon::init_attack(
	sanguis::server::entities::with_weapon &_entity
)
{
	_entity.start_attacking();

	this->on_init_attack(
		_entity
	);
}

void
sanguis::server::weapons::weapon::on_init_attack(
	sanguis::server::entities::with_weapon &
)
{
}

void
sanguis::server::weapons::weapon::on_castpoint(
	sanguis::server::entities::with_weapon &
)
{
}
