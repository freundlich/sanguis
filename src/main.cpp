#include "args/log_level.hpp"
#include "args/options.hpp"
#include "args/parse.hpp"
#include "args/sge_options.hpp"
#include "args/server_only.hpp"
#include "client/create.hpp"
#include "load/server_context.hpp"
#include "server/create.hpp"
#include "log.hpp"
#include "log_context.hpp"
#include "log_switcher.hpp"
#include "main_object.hpp"

#include <sge/log/global_context.hpp>
#include <sge/systems/instance.hpp>

#include <fcppt/io/cerr.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/global.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/text.hpp>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>

#include <exception>
#include <iostream>
#include <ostream>

#include <cstdlib>

int
main(
	int argc,
	char *argv[]
)
try
{
	boost::program_options::options_description desc(
		sanguis::args::options()
	);

#if 0
	// FIXME: why does this not work?
	sanguis::log_switcher 
		sge_log(
			boost::phoenix::ref(
				desc
			),
			FCPPT_TEXT("sge"),
			sge::log::global_context()
		),
		sanguis_log(
			boost::phoenix::ref(
				desc
			),
			FCPPT_TEXT("sanguis"),
			sanguis::log_context()
		);
#endif	
	boost::program_options::variables_map const vm(
		sanguis::args::parse(
			argc,
			argv,
			desc
		)
	);

	if(
		vm.count("help")
	)
	{
		std::cout << desc << '\n';

		return EXIT_SUCCESS;
	}

	fcppt::log::level::type const log_level(
		sanguis::args::log_level(
			vm
		)
	);

	fcppt::log::activate_levels(
		fcppt::log::global(),
		log_level
	);

	fcppt::log::activate_levels(
		sanguis::log(),
		log_level
	);

	sge::systems::instance sys(
		sanguis::args::sge_options(
			vm
		)
	);

	// has to be done after the plugins are loaded
#if 0
	sge_log.apply(
		vm
	);

	sanguis_log.apply(
		vm
	);
#endif

	bool const server_only(
		sanguis::args::server_only(
			vm
		)
	);

	typedef fcppt::scoped_ptr<
		sanguis::load::context_base
	> server_context;

	server_context context;

	// TODO: ugly!
	if(
		server_only
	)
		context.take(
			fcppt::make_unique_ptr<
				sanguis::load::server_context
			>()
		);
	
	typedef fcppt::scoped_ptr<
		sanguis::main_object
	> main_object_scoped_ptr;

	main_object_scoped_ptr obj(
		server_only
		?
			sanguis::server::create(
				sys,
				vm,
				*context
			)
		:
			sanguis::client::create(
				sys,
				vm
			)
		);
	
	return obj->run();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr
		<< FCPPT_TEXT("caught fcppt exception: ")
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< "caught standard exception: "
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}