#ifndef SANGUIS_SERVER_RANDOM_MAKE_UPPER_BOUND_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_MAKE_UPPER_BOUND_HPP_INCLUDED

#include <fcppt/literal.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace random
{

template<
	typename T,
	typename Enable = void
>
struct make_upper_bound;

template<
	typename T
>
struct make_upper_bound<
	T,
	typename
	boost::enable_if<
		std::is_floating_point<
			typename T::value_type
		>
	>::type
>
{
	using
	result_type
	=
	typename
	fcppt::random::distribution::parameters::uniform_real<
		T
	>::sup;

	static
	result_type
	execute(
		T const _value
	)
	{
		return
			result_type(
				_value
			);
	}
};

template<
	typename T
>
struct make_upper_bound<
	T,
	typename
	boost::disable_if<
		std::is_floating_point<
			typename T::value_type
		>
	>::type
>
{
	using
	result_type
	=
	typename
	fcppt::random::distribution::parameters::uniform_int<
		T
	>::max;

	static
	result_type
	execute(
		T const _value
	)
	{
		FCPPT_ASSERT_PRE(
			_value
			>
			fcppt::literal<
				T
			>(
				0
			)
		);

		return
			result_type(
				_value
				-
				fcppt::literal<
					T
				>(
					1
				)
			);
	}
};

}
}
}

#endif
