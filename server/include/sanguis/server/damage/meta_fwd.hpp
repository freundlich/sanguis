#ifndef SANGUIS_SERVER_DAMAGE_META_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_META_FWD_HPP_INCLUDED

#include <sanguis/server/damage/basic_meta_fwd.hpp>
#include <sanguis/server/damage/unit_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

typedef
sanguis::server::damage::basic_meta<
	sanguis::server::damage::unit
>
meta;

}
}
}

#endif