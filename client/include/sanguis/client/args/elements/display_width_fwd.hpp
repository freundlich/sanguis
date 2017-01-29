#ifndef SANGUIS_CLIENT_ARGS_ELEMENTS_DISPLAY_WIDTH_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_ELEMENTS_DISPLAY_WIDTH_FWD_HPP_INCLUDED

#include <sanguis/client/args/optional_screen_unit_fwd.hpp>
#include <sanguis/client/args/labels/display_width.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace args
{
namespace elements
{

typedef
fcppt::record::element<
	sanguis::client::args::labels::display_width,
	sanguis::client::args::optional_screen_unit
>
display_width;

}
}
}
}

#endif
