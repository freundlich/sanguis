#ifndef SANGUIS_CLIENT_MENU_CALLBACKS_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_CALLBACKS_OBJECT_HPP_INCLUDED

#include "connect.hpp"
#include "cancel_connect.hpp"
#include "start_server.hpp"
#include "quit.hpp"
#include <fcppt/function/object.hpp>

namespace sanguis
{
namespace client
{
namespace menu
{
namespace callbacks
{
struct object
{
public:
	object(
		connect const &,
		cancel_connect const &,
		start_server const &,
		quit const &);
	
	connect connect_;
	cancel_connect cancel_connect_;
	start_server start_server_;
	quit quit_;
};
}
}
}
}

#endif // SANGUIS_CLIENT_MENU_CALLBACKS_OBJECT_HPP_INCLUDED
