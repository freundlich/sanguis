#include <sanguis/model/part.hpp>
#include <sanguis/model/aux_/serialize/image_name.hpp>
#include <sanguis/model/aux_/serialize/part.hpp>
#include <sanguis/model/aux_/serialize/weapon_category_map.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/assign/make_container_opt.hpp>


sge::parse::json::object
sanguis::model::aux_::serialize::part(
	sanguis::model::part const &_part
)
{
	return
		sge::parse::json::object(
			fcppt::assign::make_container_opt<
				sge::parse::json::member_map
			>(
				sanguis::model::aux_::serialize::weapon_category_map(
					_part.weapon_categories()
				),
				sanguis::model::aux_::serialize::image_name(
					_part.image_name()
				)
			)
		);
}
