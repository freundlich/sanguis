#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/change_callback.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>


sanguis::server::entities::property::always_max::always_max(
	sanguis::server::entities::property::value const _base
)
:
	sanguis::server::entities::property::base(
		_base
	),
	current_(
		_base
	)
{
}

sanguis::server::entities::property::always_max::~always_max()
{
}

sanguis::server::entities::property::value
sanguis::server::entities::property::always_max::current() const
{
	return current_;
}

fcppt::signal::auto_connection
sanguis::server::entities::property::always_max::register_change_callback(
	sanguis::server::entities::property::change_callback const &_callback
)
{
	return
		change_signal_.connect(
			_callback
		);
}

void
sanguis::server::entities::property::always_max::on_recalc_max(
	sanguis::server::entities::property::value const _max
)
{
	current_ = _max;

	change_signal_(
		this->current()
	);
}
