#include "execute_end.hpp"
#include "base.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::server::collision::execute_function const
sanguis::server::collision::execute_end()
{
	static execute_function const ret(
		std::tr1::bind(
			&base::collision_end,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);

	return ret;
}