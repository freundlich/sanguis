#include "world_parameters.hpp"

sanguis::client::world_parameters::world_parameters(
	sanguis::world_id const _world_id,
	sanguis::creator::generator::top_parameters const &_top_parameters
)
:
	world_id_(_world_id),
	top_parameters_(_top_parameters)
{
}

sanguis::world_id const
sanguis::client::world_parameters::world_id() const
{
	return world_id_;
}

sanguis::creator::generator::top_parameters const &
sanguis::client::world_parameters::top_parameters() const
{
	return top_parameters_;
}