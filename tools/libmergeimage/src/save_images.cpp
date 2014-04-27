#include <sanguis/model/image_name.hpp>
#include <sanguis/tools/libmergeimage/image.hpp>
#include <sanguis/tools/libmergeimage/image_vector.hpp>
#include <sanguis/tools/libmergeimage/save_images.hpp>
#include <sanguis/tools/libmergeimage/saved_image.hpp>
#include <sanguis/tools/libmergeimage/saved_image_vector.hpp>
#include <sge/image2d/save_from_view.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::saved_image_vector
sanguis::tools::libmergeimage::save_images(
	sge::image2d::system &_image_system,
	boost::filesystem::path const &_directory,
	sanguis::tools::libmergeimage::image_vector const &_images
)
{
	sanguis::tools::libmergeimage::saved_image_vector result;

	for(
		sanguis::tools::libmergeimage::image_vector::size_type index(
			0u
		);
		index < _images.size();
		++index
	)
	{
		sanguis::tools::libmergeimage::image const &image(
			_images[
				index
			]
		);

		fcppt::string const file_name(
			fcppt::insert_to_fcppt_string(
				index
			)
			+
			FCPPT_TEXT(".png")
		);

		sge::image2d::save_from_view(
			_image_system,
			sge::image2d::view::const_object(
				image.store().wrapped_view()
			),
			_directory
			/
			file_name
		);

		result.push_back(
			sanguis::tools::libmergeimage::saved_image(
				image.paths(),
				sanguis::model::image_name(
					file_name
				)
			)
		);
	}

	return
		result;
}