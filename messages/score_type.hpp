#ifndef SANGUIS_MESSAGES_SCORE_TYPE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SCORE_TYPE_HPP_INCLUDED

#include "bindings/pod.hpp"
#include "types/score.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::pod<
	types::score
> score_type;

}
}

#endif