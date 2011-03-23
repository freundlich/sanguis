#ifndef SANGUIS_MESSAGES_ENTITY_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_ENTITY_ID_HPP_INCLUDED

#include "../entity_id.hpp"
#include "bindings/fundamental.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::fundamental<
	sanguis::entity_id
> entity_id;

}
}

#endif