#ifndef SANGUIS_CLIENT_GUI_MENU_CALLBACKS_QUIT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CALLBACKS_QUIT_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace menu
{
namespace callbacks
{

typedef std::function<
	void ()
> quit;

}
}
}
}
}

#endif