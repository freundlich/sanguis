#include <sanguis/exception.hpp>
#include <sanguis/client/args/log_level_exn.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/level_from_string.hpp>


fcppt::log::level
sanguis::client::args::log_level_exn(
	fcppt::string const &_level
)
{
	return
		fcppt::optional_to_exception(
			fcppt::log::level_from_string(
				_level
			),
			[
				&_level
			]{
				return
					sanguis::exception{
						FCPPT_TEXT("Invalid log level ")
						+
						_level
					};
			}
		);
}