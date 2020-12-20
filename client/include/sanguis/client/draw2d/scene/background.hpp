#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_HPP_INCLUDED

#include <sanguis/client/draw2d/translation_fwd.hpp>
#include <sanguis/client/draw2d/scene/background_fwd.hpp>
#include <sanguis/client/draw2d/sprite/client/object_decl.hpp>
#include <sanguis/client/draw2d/sprite/client/system_fwd.hpp>
#include <sanguis/client/load/context_cref.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

class background
{
	FCPPT_NONCOPYABLE(
		background
	);
public:
	background(
		sanguis::client::load::context_cref,
		sanguis::client::draw2d::sprite::client::system &,
		sge::viewport::manager &
	);

	~background();

	void
	render(
		sge::renderer::context::core &,
		sanguis::client::draw2d::translation
	);
private:
	void
	reset_viewport();

	sanguis::client::draw2d::sprite::client::system &client_system_;

	sge::texture::part const &texture_;

	sanguis::client::draw2d::sprite::client::object sprite_;

	fcppt::signal::auto_connection const viewport_connection_;
};

}
}
}
}

#endif
