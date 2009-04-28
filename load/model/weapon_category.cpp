#include "weapon_category.hpp"
#include "base_animation_not_found.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/filesystem/exists.hpp>
#include <sge/algorithm/find_exn.hpp>
#include <sge/log/headers.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>
#include <boost/tr1/array.hpp>
#include <boost/variant/get.hpp>
#include <boost/foreach.hpp>
#include <utility>
#include <iterator>

namespace
{

typedef std::tr1::array<
	sge::string,
	sanguis::animation_type::size
> animation_type_array;

animation_type_array const animation_types = {{
	SGE_TEXT("none"),
	SGE_TEXT("attacking"),
	SGE_TEXT("walking"),
	SGE_TEXT("dying"),
	SGE_TEXT("deploying"),
	SGE_TEXT("reloading")
}};

sanguis::animation_type::type
find_animation_type(
	sge::string const &str)
{
	return static_cast<
		sanguis::animation_type::type
	>(
		std::distance(
			animation_types.begin(),
			sge::algorithm::find_exn(
				animation_types.begin(),
				animation_types.end(),
				str
			)
		)
	);
}

}

sanguis::load::model::animation const &
sanguis::load::model::weapon_category::operator[](
	animation_type::type const anim) const
{
	animation_map::const_iterator const it(animations.find(anim));
	if(it != animations.end())
		return it->second;

	if(anim == animation_type::none)
		throw exception(
			SGE_TEXT("Default animation not found in TODO")
		);
	throw base_animation_not_found(
		anim);
}

sanguis::load::model::weapon_category::weapon_category(
	sge::parse::json::value const &val,
	global_parameters const &param)
:
	animations()
{
	BOOST_FOREACH(
		sge::parse::json::element_vector::const_reference r,
		boost::get<
			sge::parse::json::array
		>(
			val	
		).elements
	)
	{
		sge::parse::json::member const &member(
			boost::get<
				sge::parse::json::object
			>(
				r
			).members.at(0)
		);

		if(
			animations.insert(
				std::make_pair(
					find_animation_type(
						member.name
					),
					animation(
						member.value_,
						param
					)
				)
			).second == false
		)
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< SGE_TEXT("Double insert in weapon_category!")
			);
	}
}
