#ifndef SANGUIS_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/load/context_base.hpp>
#include <sanguis/load/model/context.hpp>
#include <sanguis/load/resource/context.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace load
{

class context
:
	public context_base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context(
		sge::image2d::system &,
		sge::renderer::device &,
		sge::audio::loader &,
		sge::audio::player &
	);

	~context();

	resource::context const &
	resources() const;

	model::context const &
	models() const;
private:
	// context_base overrides
	sge::renderer::dim2 const
	model_dim(
		fcppt::string const &
	) const;

	sge::image2d::system &il_;

	sge::renderer::device &rend_;

	sge::audio::loader &ml_;

	sge::audio::player &ap_;

	resource::context const resource_ctx_;

	model::context const model_ctx_;
};

}
}

#endif
