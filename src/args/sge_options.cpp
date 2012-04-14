#include <sanguis/args/sge_options.hpp>
#include <sanguis/args/multi_sampling.hpp>
#include <sanguis/args/screen_mode.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/systems/charconv.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/title.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/text.hpp>

sge::systems::list const
sanguis::args::sge_options(
	boost::program_options::variables_map const &_vm
)
{
	sge::window::dim const dimensions(
		1024,
		768
	);

	return
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sanguis")
					),
					dimensions
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					args::screen_mode(
						_vm
					),
					sge::renderer::depth_stencil_buffer::d24s8,
					sge::renderer::vsync::on,
					sge::renderer::multi_sample_type(
						args::multi_sampling(
							_vm
						)
					)
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				|
				sge::systems::input_helper::cursor_demuxer,
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::image2d(
				sge::image::capabilities_field(
					sge::image::capabilities::threadsafe
				),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<
						sge::media::extension_set
					>(
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					)
				)
			)
		)
		(
			sge::systems::font() // TODO: make sure that we can load truetype fonts, use a multi loader here as well!
		)
		(
			sge::systems::charconv()
		);
}
