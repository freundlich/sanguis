#ifndef SANGUIS_LOAD_MODEL_ANIMATION_OBJECT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "context_fwd.hpp"
#include "context_ptr.hpp"
#include "sound_fwd.hpp"
#include "../global_parameters.hpp"
#include "../frame_cache.hpp"
#include "../../resource/texture_context.hpp"
#include "../../resource/texture_identifier.hpp"
#include "../../resource/context_fwd.hpp"
#include <sge/texture/part_fwd.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace model
{
namespace animation
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	model::animation::sound const &
	sounds() const;

	model::animation::context_ptr
	load() const;

	~object();

	object(
		sge::parse::json::object const &,
		model::global_parameters const &
	);
private:
	sge::parse::json::object object_;

	model::global_parameters param_;

	fcppt::scoped_ptr<
		animation::sound
	> sounds_;

	mutable frame_cache frame_cache_;

	resource::texture_identifier texture_;

	void
	fill_cache(
		sge::renderer::lock_rect const &
	) const;
};

}
}
}
}

#endif