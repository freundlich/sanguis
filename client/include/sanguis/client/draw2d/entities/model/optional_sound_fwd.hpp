#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OPTIONAL_SOUND_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OPTIONAL_SOUND_FWD_HPP_INCLUDED

#include <sge/audio/sound/base_unique_ptr.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

typedef
fcppt::optional<
	sge::audio::sound::base_unique_ptr
>
optional_sound;

}
}
}
}
}

#endif