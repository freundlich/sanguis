#ifndef SANGUIS_CREATOR_AUX_SERIALIZATION_OPENING_CONTAINER_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_SERIALIZATION_OPENING_CONTAINER_HPP_INCLUDED

#include <sanguis/creator/opening_container.hpp>
#include <sge/parse/json/array_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace serialization
{

sge::parse::json::array
opening_container(
	sanguis::creator::opening_container const &
);

}
}
}
}

#endif
