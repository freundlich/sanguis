#ifndef SANGUIS_DURATION_HPP_INCLUDED
#define SANGUIS_DURATION_HPP_INCLUDED

#include <sanguis/time_unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{

typedef
std::chrono::duration<
	sanguis::time_unit
>
duration;

}

#endif