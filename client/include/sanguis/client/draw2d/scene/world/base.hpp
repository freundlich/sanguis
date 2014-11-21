#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BASE_HPP_INCLUDED

#include <sanguis/client/slowed_duration_fwd.hpp>
#include <sanguis/client/draw2d/player_center_fwd.hpp>
#include <sanguis/client/draw2d/z_ordering_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/base_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base() = 0;

	virtual
	void
	update(
		sanguis::client::slowed_duration
	) = 0;

	virtual
	void
	draw_after(
		sge::renderer::context::core &,
		sanguis::client::draw2d::player_center,
		sanguis::client::draw2d::z_ordering
	) = 0;
};

}
}
}
}
}

#endif
