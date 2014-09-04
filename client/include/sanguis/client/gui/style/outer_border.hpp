#ifndef SANGUIS_CLIENT_GUI_STYLE_OUTER_BORDER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_STYLE_OUTER_BORDER_HPP_INCLUDED

#include <sge/rucksack/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace gui
{
namespace style
{

typedef
std::integral_constant<
	sge::rucksack::scalar,
	0
>
outer_border;

}
}
}
}

#endif
