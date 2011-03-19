#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_STATE_HPP_INCLUDED

#include "part_fwd.hpp"
#include "../../../../load/model/part_fwd.hpp"
#include "../../../../load/model/animation_fwd.hpp"
#include "../../../../animation_type.hpp"
#include "../../../../weapon_type.hpp"
#include <sge/audio/sound/positional_ptr.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <fcppt/noncopyable.hpp>

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

class part_state
{
	FCPPT_NONCOPYABLE(
		part_state
	);
public:
	part_state(
		load::model::part const &,
		part &,
		animation_type::type,
		weapon_type::type
	);

	sanguis::animation_type::type
	animation_type() const;

	sanguis::weapon_type::type
	weapon_type() const;

	void
	update();

	~part_state();
private:
	part &ref_;

	load::model::animation const &anim_;

	sge::audio::sound::positional_ptr const
		sstart_,
		srunning_,
		send_;

	animation_type::type const animation_type_;

	weapon_type::type const weapon_type_;

	bool start_played_;

	void
	play(
		sge::audio::sound::positional_ptr,
		sge::audio::sound::repeat::type = sge::audio::sound::repeat::once
	);
	
	void
	update_sound(
		sge::audio::sound::positional_ptr
	);

	void
	init_sound(
		sge::audio::sound::positional_ptr
	);

	void
	update_sounds();
};

}
}
}
}
}

#endif
