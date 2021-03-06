#ifndef SANGUIS_MODEL_WEAPON_CATEGORY_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_WEAPON_CATEGORY_MAP_HPP_INCLUDED

#include <sanguis/model/weapon_category.hpp>
#include <sanguis/model/weapon_category_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace model
{

using
weapon_category_map
=
std::unordered_map<
	sanguis::model::weapon_category_name,
	sanguis::model::weapon_category
>;

}
}

#endif
