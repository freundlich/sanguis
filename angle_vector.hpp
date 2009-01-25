#ifndef SANGUIS_ANGLE_VECTOR_HPP_INCLUDED
#define SANGUIS_ANGLE_VECTOR_HPP_INCLUDED

#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/static.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <cmath>

namespace sanguis
{

template<
	typename T
>
typename boost::enable_if<
	boost::is_floating_point<T>,
	typename sge::math::vector::static_<T, 2>::type
>::type
	angle_to_vector(
		T const angle)
{
	return typename sge::math::vector::static_<
		T,
		2
	>::type(
		std::cos(angle),
		std::sin(angle));
}

}

#endif
