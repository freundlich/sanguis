#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/name.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>


sanguis::client::draw2d::entities::model::parameters::parameters(
	sanguis::client::draw2d::entities::model::load_parameters const &_load_parameters,
	sanguis::client::draw2d::entities::model::name const &_name,
	sanguis::client::draw2d::entities::order_vector const &_orders,
	sanguis::client::optional_health_pair const &_health_pair,
	sanguis::client::draw2d::entities::model::decay_option const _decay_option
)
:
	load_parameters_(
		_load_parameters
	),
	name_(
		_name
	),
	orders_(
		_orders
	),
	health_pair_(
		_health_pair
	),
	decay_option_(
		_decay_option
	)
{
}

sanguis::client::draw2d::entities::model::load_parameters const &
sanguis::client::draw2d::entities::model::parameters::load_parameters() const
{
	return
		load_parameters_;
}

sanguis::client::draw2d::entities::model::name const &
sanguis::client::draw2d::entities::model::parameters::name() const
{
	return
		name_;
}

sanguis::client::draw2d::entities::order_vector const &
sanguis::client::draw2d::entities::model::parameters::orders() const
{
	return
		orders_;
}

sanguis::client::optional_health_pair const &
sanguis::client::draw2d::entities::model::parameters::health_pair() const
{
	return
		health_pair_;
}

sanguis::client::draw2d::entities::model::decay_option
sanguis::client::draw2d::entities::model::parameters::decay_option() const
{
	return
		decay_option_;
}