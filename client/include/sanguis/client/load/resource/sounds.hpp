#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_SOUNDS_HPP_INCLUDED

#include <sanguis/client/load/resource/optional_sound_fwd.hpp>
#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{

class sounds
{
	FCPPT_NONCOPYABLE(
		sounds
	);
public:
	sounds(
		sge::audio::loader &,
		sge::audio::player &
	);

	~sounds();

	sanguis::client::load::resource::optional_sound const
	load(
		fcppt::string const &
	) const;

	sanguis::client::load::resource::optional_sound const
	load_path(
		boost::filesystem::path const &
	) const;
private:
	typedef
	fcppt::optional<
		sge::audio::buffer_unique_ptr
	>
	optional_buffer;

	typedef
	std::map<
		boost::filesystem::path,
		optional_buffer
	>
	buffer_map;

	sge::audio::loader &multi_loader_;

	sge::audio::player &player_;

	mutable buffer_map buffers_;
};

}
}
}
}

#endif
