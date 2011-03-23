#include "animation_sound.hpp"
#include "../log.hpp"
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <fcppt/algorithm/find_exn.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <boost/foreach.hpp>
#include <utility>
#include <iterator>

namespace
{

typedef fcppt::container::array<
	fcppt::string,
	sanguis::animation_sound_type::size
> animation_sound_array;

animation_sound_array const animation_sounds = {{
	FCPPT_TEXT("start"),
	FCPPT_TEXT("running"),
	FCPPT_TEXT("end")
}};

sanguis::animation_sound_type::type
find_sound_type(
	fcppt::string const &name)
{
	return static_cast<
		sanguis::animation_sound_type::type
	>(
		std::distance(
			animation_sounds.begin(),
			fcppt::algorithm::find_exn(
				animation_sounds.begin(),
				animation_sounds.end(),
				name
			)
		)
	);
}

}

sge::audio::sound::positional_ptr const
sanguis::load::model::animation_sound::operator[](
	animation_sound_type::type const stype) const
{
	animation_sound_map::const_iterator const it(
		sounds.find(
			stype
		)
	);
	
	return it == sounds.end()
		? sge::audio::sound::positional_ptr()
		: it->second.random();
}

sanguis::load::model::animation_sound::animation_sound()
:
	sounds()
{}

sanguis::load::model::animation_sound::animation_sound(
	sge::parse::json::member_vector const &members,
	resource::sounds const &ctx)
:
	sounds()
{
	BOOST_FOREACH(
		sge::parse::json::member_vector::const_reference ref,
		members
	)
	{
		if(
			sounds.insert(
				std::make_pair(
					find_sound_type(
						ref.name
					),
					conditional_sound(
						sge::parse::json::get<
							sge::parse::json::object
						>(
							ref.value
						).members,
						ctx
					)
				)
			).second == false
		)
			FCPPT_LOG_WARNING(
				log(),
				fcppt::log::_
					<< FCPPT_TEXT("Double insert in sounds!")
			);
	}
}