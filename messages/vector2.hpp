#ifndef SANGUIS_MESSAGES_VECTOR2_HPP_INCLUDED
#define SANGUIS_MESSAGES_VECTOR2_HPP_INCLUDED

#include "bindings/static.hpp"
#include "bindings/pod.hpp"
#include "types/vector2.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::static_<
	types::vector2,
	bindings::pod
> vector2;

}
}

#endif
