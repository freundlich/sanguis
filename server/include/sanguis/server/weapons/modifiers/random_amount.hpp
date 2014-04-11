#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_RANDOM_AMOUNT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_RANDOM_AMOUNT_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/random/amount.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace modifiers
{

sanguis::server::random::amount const
random_amount(
	sanguis::random_generator &,
	sanguis::server::random::amount
);

}
}
}
}

#endif