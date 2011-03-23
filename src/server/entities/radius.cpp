#include "radius.hpp"
#include <fcppt/math/quad.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <cmath>

sanguis::server::space_unit
sanguis::server::entities::radius(
	dim_type const &d)
{
	return std::sqrt(
		fcppt::math::quad(d.w() / 2)
		+ fcppt::math::quad(d.h() / 2)
	);
}