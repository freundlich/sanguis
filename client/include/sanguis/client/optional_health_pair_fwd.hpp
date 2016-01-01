#ifndef SANGUIS_CLIENT_OPTIONAL_HEALTH_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_OPTIONAL_HEALTH_PAIR_FWD_HPP_INCLUDED

#include <sanguis/client/health_pair_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace client
{

typedef
fcppt::optional::object<
	sanguis::client::health_pair
>
optional_health_pair;

}
}

#endif
