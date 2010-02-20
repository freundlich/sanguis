#ifndef SANGUIS_ARGS_CLIENT_SGE_OPTIONS_HPP_INCLUDED
#define SANGUIS_ARGS_CLIENT_SGE_OPTIONS_HPP_INCLUDED

#include <sge/systems/list.hpp>
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace args
{

sge::systems::list const
client_sge_options(
	boost::program_options::variables_map const &
);

}
}

#endif
