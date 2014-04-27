#include <sanguis/server/create.hpp>
#include <sanguis/server/object_base.hpp>
#include <sanguis/server/object_base_unique_ptr.hpp>
#include <alda/net/port.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <iostream>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>


int
main(
	int argc,
	char **argv
)
try
{
	// TODO: Use arguments
	sanguis::server::object_base_unique_ptr const server(
		sanguis::server::create(
			// TODO
			alda::net::port(
				31337u
			)
		)
	);

	server->run();

	return
		EXIT_SUCCESS;
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<<
		FCPPT_TEXT("Caught fcppt exception: ")
		<<
		_error.string()
		<<
		FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cout
		<<
		"Caught standard exception: "
		<<
		_error.what()
		<<
		'\n';

	return
		EXIT_FAILURE;
}