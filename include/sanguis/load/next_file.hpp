#ifndef SANGUIS_LOAD_NEXT_FILE_HPP_INCLUDED
#define SANGUIS_LOAD_NEXT_FILE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{

boost::filesystem::directory_iterator const
next_file(
	boost::filesystem::directory_iterator
);

}
}

#endif
