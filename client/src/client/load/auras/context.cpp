#include <sanguis/aura_type.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/client/load/auras/context.hpp>
#include <sanguis/client/load/auras/lookup_name.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sanguis/client/load/resource/textures_cref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/iterator/make_range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::auras::context::context(
	sanguis::client::load::resource::textures_cref const _resources
)
:
	textures_(
		fcppt::algorithm::map<
			texture_map
		>(
			fcppt::iterator::make_range(
				std::filesystem::directory_iterator(
					sanguis::media_path()
					/
					FCPPT_TEXT("auras")
				),
				std::filesystem::directory_iterator()
			),
			[
				&_resources
			](
				std::filesystem::path const &_path
			)
			{
				return
					std::make_pair(
						sanguis::client::load::auras::lookup_name(
							fcppt::filesystem::stem(
								_path
							)
						),
						fcppt::make_cref(
							_resources->load(
								_path
							)
						)
					);
			}
		)
	)
{
}

sanguis::client::load::auras::context::~context()
= default;

sge::texture::part const &
sanguis::client::load::auras::context::texture(
	sanguis::aura_type const _aura_type
)
{
	auto const it(
		textures_.find(
			_aura_type
		)
	);

	// TODO(philipp): Better error
	FCPPT_ASSERT_ERROR(
		it != textures_.end()
	);

	return
		it->second.get();
}
