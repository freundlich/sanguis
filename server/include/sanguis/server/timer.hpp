#ifndef SANGUIS_SERVER_TIMER_HPP_INCLUDED
#define SANGUIS_SERVER_TIMER_HPP_INCLUDED

#include <sanguis/io_service_fwd.hpp>
#include <sanguis/server/timer_callback.hpp>
#include <sanguis/server/timer_duration.hpp>
#include <sanguis/server/timer_fwd.hpp>
#include <sanguis/server/timer_impl_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

class timer
{
	FCPPT_NONCOPYABLE(
		timer
	);
public:
	timer(
		sanguis::io_service const &,
		sanguis::server::timer_callback const &,
		sanguis::server::timer_duration const &
	);

	~timer();
private:
	std::unique_ptr<
		sanguis::server::timer_impl
	> const impl_;
};

}
}

#endif