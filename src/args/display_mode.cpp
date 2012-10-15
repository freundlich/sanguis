#include <sanguis/args/display_mode.hpp>
#include <sanguis/args/optional_resolution.hpp>
#include <sanguis/args/resolution.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sge::renderer::display_mode::optional_object const
sanguis::args::display_mode(
	boost::program_options::variables_map const &_vm
)
{
	sanguis::args::optional_resolution const res(
		sanguis::args::resolution(
			_vm
		)
	);

	return
		res
		?
			sge::renderer::display_mode::optional_object(
				sge::renderer::display_mode::object(
					sge::renderer::display_mode::pixel_size(
						*res
					),
					sge::renderer::display_mode::optional_dimensions(),
					sge::renderer::display_mode::optional_refresh_rate()
				)
			)
		:
			sge::renderer::display_mode::optional_object()
		;
}
