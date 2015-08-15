#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_ORDER_FUNCTION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_ORDER_FUNCTION_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering_fwd.hpp>
#include <sanguis/client/draw2d/sprite/index_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

typedef
fcppt::function<
	sanguis::client::draw2d::z_ordering (
		sanguis::client::draw2d::sprite::index
	)
>
order_function;

}
}
}
}

#endif
