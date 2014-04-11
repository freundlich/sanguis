#include <sanguis/client/args/log_level.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/level_from_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


fcppt::log::level
sanguis::client::args::log_level(
	boost::program_options::variables_map const &_vm
)
{
	return
		fcppt::log::level_from_string(
			fcppt::from_std_string(
				_vm["log"].as<
					std::string
				>()
			)
		);
}