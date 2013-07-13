#ifndef SANGUIS_CREATOR_AUX_DESERIALIZATION_OPENING_CONTAINER_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_DESERIALIZATION_OPENING_CONTAINER_HPP_INCLUDED

#include <sanguis/creator/opening_container.hpp>
#include <sge/parse/json/array_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace deserialization
{

sanguis::creator::opening_container
opening_container(
	sge::parse::json::array const &
);

}
}
}
}

#endif
