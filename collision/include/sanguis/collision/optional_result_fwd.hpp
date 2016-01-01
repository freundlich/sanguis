#ifndef SANGUIS_COLLISION_OPTIONAL_RESULT_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_OPTIONAL_RESULT_FWD_HPP_INCLUDED

#include <sanguis/collision/result_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace collision
{

typedef
fcppt::optional::object<
	sanguis::collision::result
>
optional_result;

}
}

#endif
