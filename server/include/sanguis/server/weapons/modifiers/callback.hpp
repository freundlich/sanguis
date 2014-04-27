#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_CALLBACK_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <fcppt/reference_wrapper_impl.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace modifiers
{

template<
	typename Parameters
>
using
callback
=
void
(*)(
	sanguis::random_generator &,
	sanguis::server::entities::enemies::difficulty,
	fcppt::reference_wrapper<
		Parameters
	>
);

}
}
}
}

#endif