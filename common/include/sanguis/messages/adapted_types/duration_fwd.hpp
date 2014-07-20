#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_DURATION_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_DURATION_FWD_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/messages/adapted_types/time_unit_fwd.hpp>
#include <alda/bindings/duration_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef
alda::bindings::duration<
	sanguis::messages::adapted_types::time_unit,
	sanguis::duration::period
>
duration;

}
}
}

#endif