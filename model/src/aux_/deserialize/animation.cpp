#include <sanguis/model/animation.hpp>
#include <sanguis/model/aux_/deserialize/animation.hpp>
#include <sanguis/model/aux_/deserialize/animation_delay.hpp>
#include <sanguis/model/aux_/deserialize/animation_sound.hpp>
#include <sanguis/model/aux_/deserialize/animation_range.hpp>
#include <sanguis/model/aux_/deserialize/image_name.hpp>
#include <sanguis/model/aux_/deserialize/weapon_category_map.hpp>
#include <sge/parse/json/object_fwd.hpp>


sanguis::model::animation
sanguis::model::aux_::deserialize::animation(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::animation(
			sanguis::model::aux_::deserialize::animation_range(
				_object
			),
			sanguis::model::aux_::deserialize::animation_delay(
				_object
			),
			sanguis::model::aux_::deserialize::animation_sound(
				_object
			),
			sanguis::model::aux_::deserialize::image_name(
				_object
			)
		);
}
