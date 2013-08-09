#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_WORLD_ID_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_WORLD_ID_FWD_HPP_INCLUDED

#include <sanguis/world_id_fwd.hpp>
#include <alda/bindings/fundamental_strong_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef
alda::bindings::fundamental_strong<
	sanguis::world_id
>
world_id;

}
}
}

#endif