#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_MODIFIERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_MODIFIERS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/modifiers/container.hpp>
#include <sanguis/server/random/amount.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{
namespace factory
{

sanguis::server::entities::enemies::modifiers::container
make_modifiers(
	sanguis::random_generator &,
	sanguis::server::random::amount
);

}
}
}
}
}

#endif
