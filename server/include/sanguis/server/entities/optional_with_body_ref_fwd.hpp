#ifndef SANGUIS_SERVER_ENTITIES_OPTIONAL_WITH_BODY_REF_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_OPTIONAL_WITH_BODY_REF_FWD_HPP_INCLUDED

#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

typedef
fcppt::optional::object<
	sanguis::server::entities::with_body &
>
optional_with_body_ref;

}
}
}

#endif
