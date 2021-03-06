#ifndef SANGUIS_SERVER_RANDOM_DISTRIBUTOR_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_DISTRIBUTOR_IMPL_HPP_INCLUDED

#include <sanguis/random_generator.hpp>
#include <sanguis/server/random/distributor_decl.hpp>
#include <sanguis/server/random/make_upper_bound.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_impl.hpp>


template<
	typename Value,
	typename State
>
sanguis::server::random::distributor<
	Value,
	State
>::distributor(
	vector const &_values
)
:
	values_(
		_values
	),
	distribution_(
		distribution_parameters(
			typename
			distribution_parameters::min(
				fcppt::literal<
					Value
				>(
					0
				)
			),
			sanguis::server::random::make_upper_bound<
				Value
			>::execute(
				fcppt::algorithm::fold(
					_values,
					fcppt::literal<
						Value
					>(
						0
					),
					[](
						value_state_pair const &_pair,
						Value const _cur
					)
					{
						return
							_cur
							+
							_pair.first;
					}
				)
			)
		)
	)
{
	FCPPT_ASSERT_PRE(
		!values_.empty()
	);
}

namespace sanguis::server::random
{
template<
	typename Value,
	typename State
>
distributor<
	Value,
	State
>::~distributor()
= default;
}

template<
	typename Value,
	typename State
>
State const &
sanguis::server::random::distributor<
	Value,
	State
>::execute(
	sanguis::random_generator &_random_generator
)
{
	Value const bound(
		distribution_(
			_random_generator
		)
	);

	Value cur(
		fcppt::literal<
			Value
		>(
			0U
		)
	);

	for(
		auto const &next
		:
		values_
	)
	{
		cur += next.first;

		if(
			bound < cur
		)
		{
			return
				next.second;
		}
	}

	// TODO(philipp): This should not happen for integers!

	return
		values_.back().second;
}

#endif
