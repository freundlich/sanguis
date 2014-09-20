#ifndef SANGUIS_LOAD_MODEL_PATH_FWD_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PATH_FWD_HPP_INCLUDED

#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

FCPPT_MAKE_STRONG_TYPEDEF(
	boost::filesystem::path,
	path
);

}
}
}

#endif
