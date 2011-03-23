#ifndef SANGUIS_MESSAGES_TYPES_ENUM_VECTOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_ENUM_VECTOR_HPP_INCLUDED

#include "enum.hpp"
#include <fcppt/container/raw_vector_fwd.hpp>

namespace sanguis
{
namespace messages
{
namespace types
{

typedef fcppt::container::raw_vector<
	enum_
> enum_vector;

}
}
}

#endif