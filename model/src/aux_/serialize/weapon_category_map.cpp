#include <sanguis/model/weapon_category_map.hpp>
#include <sanguis/model/aux_/serialize/map.hpp>
#include <sanguis/model/aux_/serialize/weapon_category.hpp>
#include <sanguis/model/aux_/serialize/weapon_category_map.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/text.hpp>


sge::parse::json::member
sanguis::model::aux_::serialize::weapon_category_map(
	sanguis::model::weapon_category_map const &_weapon_categories
)
{
	return
		sanguis::model::aux_::serialize::map(
			_weapon_categories,
			FCPPT_TEXT("weapon_categories"),
			&sanguis::model::aux_::serialize::weapon_category
		);
}