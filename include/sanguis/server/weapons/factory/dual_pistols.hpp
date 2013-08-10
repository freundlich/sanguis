#ifndef SANGUIS_SERVER_WEAPONS_FACTORY_DUAL_PISTOLS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_FACTORY_DUAL_PISTOLS_HPP_INCLUDED

#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/parameters_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace factory
{

sanguis::server::weapons::unique_ptr
dual_pistols(
	sanguis::server::weapons::factory::parameters const &
);

}
}
}
}

#endif
