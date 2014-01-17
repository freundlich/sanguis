#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_ACCURACY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_ACCURACY_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/modifiers/random_increase.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cmath>
#include <fcppt/config/external_end.hpp>


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
void
accuracy(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::difficulty const _difficulty,
	fcppt::reference_wrapper<
		Parameters
	> const _parameters
)
{
	_parameters.get().accuracy(
		std::min(
			_parameters.get().accuracy()
			+
			// TODO: What to use here?
			sanguis::server::weapons::accuracy(
				1.f
				-
				std::exp(
					-std::sqrt(
						sanguis::server::weapons::modifiers::random_increase(
							_random_generator,
							_difficulty
						)
					)
					/
					100.f
				)
			),
			sanguis::server::weapons::accuracy(
				1.f
			)
		)
	);
}

}
}
}
}

#endif
