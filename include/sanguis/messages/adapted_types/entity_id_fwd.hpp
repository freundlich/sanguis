#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_ENTITY_ID_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_ENTITY_ID_FWD_HPP_INCLUDED

#include <sanguis/entity_id_fwd.hpp>
#include <alda/bindings/fundamental_strong_decl.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef alda::bindings::fundamental_strong<
	sanguis::entity_id
> entity_id;

}
}
}

#endif