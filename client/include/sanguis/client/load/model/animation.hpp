#ifndef SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include <sanguis/client/load/model/animation_fwd.hpp>
#include <sanguis/client/load/model/optional_sound.hpp>
#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/resource/animation/series.hpp>
#include <sanguis/model/animation_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

class animation
{
	FCPPT_NONCOPYABLE(
		animation
	);
public:
	animation(
		sanguis::model::animation const &,
		sanguis::client::load::model::global_parameters const &
	);

	~animation();

	sanguis::client::load::resource::animation::series const &
	series() const;

	sanguis::client::load::model::optional_sound const &
	sound() const;
private:
	sge::texture::const_part_shared_ptr const texture_;

	sanguis::client::load::resource::animation::series const series_;

	sanguis::client::load::model::optional_sound const sound_;
};

}
}
}
}

#endif
