#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_index.hpp>
#include <sanguis/model/animation_name.hpp>
#include <sanguis/model/animation_range.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part_map.hpp>
#include <sanguis/model/part_name.hpp>
#include <sanguis/model/weapon_category_name.hpp>
#include <sanguis/tools/libmergeimage/path.hpp>
#include <sanguis/tools/libmergeimage/path_count_pair.hpp>
#include <sanguis/tools/libmergeimage/saved_image.hpp>
#include <sanguis/tools/libmergeimage/saved_image_vector.hpp>
#include <sanguis/tools/libmergeimage/to_model.hpp>
#include <sanguis/tools/libmergeimage/aux_/tree_depth.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::model::object
sanguis::tools::libmergeimage::to_model(
	sanguis::model::cell_size const _cell_size,
	sanguis::tools::libmergeimage::saved_image_vector const &_images
)
{
	sanguis::model::object result(
		_cell_size,
		sanguis::model::optional_animation_delay(),
		sanguis::model::part_map(),
		sanguis::model::optional_image_name()
	);

	for(
		sanguis::tools::libmergeimage::saved_image const &image
		:
		_images
	)
	{
		sanguis::model::animation_index cell_index(
			0u
		);

		for(
			sanguis::tools::libmergeimage::path_count_pair const &element
			:
			image.paths()
		)
		{
			sanguis::tools::libmergeimage::path const &path(
				element.path()
			);

			FCPPT_ASSERT_ERROR(
				path.size()
				==
				sanguis::tools::libmergeimage::aux_::tree_depth::value
			);

			sanguis::model::animation_index const range(
				fcppt::cast::size<
					sanguis::model::animation_index
				>(
					element.count()
				)
			);

			result[
				sanguis::model::part_name(
					path[
						0
					]
				)
			][
				sanguis::model::weapon_category_name(
					path[
						1
					]
				)
			].insert(
				sanguis::model::animation_name(
					path[
						2
					]
				),
				sanguis::model::animation(
					sanguis::model::animation_range(
						cell_index,
						cell_index
						+
						range
					),
					sanguis::model::optional_animation_delay(),
					sanguis::model::optional_animation_sound(),
					sanguis::model::optional_image_name(
						image.image_name()
					)
				)
			);

			cell_index +=
				range;
		}
	}

	return
		std::move(
			result
		);
}