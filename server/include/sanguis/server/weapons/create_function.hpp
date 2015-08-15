#ifndef SANGUIS_SERVER_WEAPONS_CREATE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CREATE_FUNCTION_HPP_INCLUDED

#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

typedef
fcppt::function<
	sanguis::server::weapons::unique_ptr ()
>
create_function;

}
}
}

#endif
