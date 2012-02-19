#include <sanguis/net/log_location.hpp>
#include <sanguis/log_location.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/text.hpp>

fcppt::log::location const
sanguis::net::log_location()
{
	return
		sanguis::log_location()
		/
		FCPPT_TEXT("net");
}