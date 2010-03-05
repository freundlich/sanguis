#include "log_level.hpp"
#include <fcppt/log/level_from_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <string>

fcppt::log::level::type
sanguis::args::log_level(
	boost::program_options::variables_map const &vm
)
{
	return
		fcppt::log::level_from_string(
			fcppt::from_std_string(
				vm["log"].as<
					std::string
				>()
			)
		);
}
