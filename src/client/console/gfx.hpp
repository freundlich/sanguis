#ifndef SANGUIS_CLIENT_CONSOLE_GFX_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_GFX_HPP_INCLUDED

#include <sge/console/gfx.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/output_line_limit.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/image2d/multi_loader_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace console
{

class gfx
{
	FCPPT_NONCOPYABLE(
		gfx
	);
public:
	gfx(
		sge::console::object &,
		sge::renderer::device &,
		sge::font::metrics &,
		sge::image2d::multi_loader &,
		sge::input::keyboard::device &,
		sge::viewport::manager &,
		sge::console::output_line_limit
	);

	~gfx();

	sge::console::gfx &
	get();
private:
	void
	on_resize();

	sge::renderer::device &renderer_;

	sge::console::gfx impl_;

	fcppt::signal::scoped_connection const resize_connection_;
};

}
}
}

#endif
