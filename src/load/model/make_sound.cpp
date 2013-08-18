#include <sanguis/load/model/make_sound.hpp>
#include <sanguis/load/model/optional_sound.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/string.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>


sanguis::load::model::optional_sound
sanguis::load::model::make_sound(
	sge::parse::json::object const &_object,
	sanguis::load::resource::sounds const &_sounds
)
{
	typedef fcppt::optional<
		sge::parse::json::string const &
	> optional_string;

	optional_string const sound(
		sge::parse::json::find_member<
			sge::parse::json::string
		>(
			_object.members,
			FCPPT_TEXT("sound")
		)
	);

	return
		sound
		?
			sanguis::load::model::optional_sound(
				sanguis::load::model::sound(
					*sound,
					_sounds
				)
			)
		:
			sanguis::load::model::optional_sound()
		;
}