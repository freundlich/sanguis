#include <sanguis/log_location.hpp>
#include <sanguis/server/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location
sanguis::server::log_location()
{
	return
		sanguis::log_location()
		/
		FCPPT_TEXT("server");
}
