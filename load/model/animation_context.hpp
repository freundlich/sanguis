#ifndef SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_HPP_INCLUDED

#include "../resource/texture_context.hpp"
#include "frame_cache.hpp"
#include <sge/sprite/animation_series.hpp>
#include <sge/scoped_ptr.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <boost/function.hpp>

namespace sanguis
{
namespace load
{
namespace model
{
class animation_context
{
public:
	typedef boost::function<void (sge::renderer::lock_rect const &)> cache_callback;

	animation_context(
		resource::texture_context const &,
		frame_cache const &,
		cache_callback const &);
	void update();
	bool is_finished() const;
	sge::sprite::animation_series const &result() const;
private:
	resource::texture_context texture_context_;
	frame_cache const &frame_cache_;
	cache_callback cache_callback_;
	bool is_finished_;
	sge::sprite::animation_series animation_;
};
}
}
}

#endif