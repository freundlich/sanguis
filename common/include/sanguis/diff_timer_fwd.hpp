#ifndef SANGUIS_DIFF_TIMER_FWD_HPP_INCLUDED
#define SANGUIS_DIFF_TIMER_FWD_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sge/timer/basic_fwd.hpp>


namespace sanguis
{

typedef
sge::timer::basic<
	sanguis::diff_clock
>
diff_timer;

}

#endif
