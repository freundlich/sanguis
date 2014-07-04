#ifndef SANGUIS_GUI_AUX__IMAGE_SPRITE_CHOICES_HPP_INCLUDED
#define SANGUIS_GUI_AUX__IMAGE_SPRITE_CHOICES_HPP_INCLUDED

#include <sanguis/gui/aux_/sprite_type_choices.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>



namespace sanguis
{
namespace gui
{
namespace aux_
{

typedef
sge::sprite::config::choices<
	sanguis::gui::aux_::sprite_type_choices,
	sge::sprite::config::normal_size,
	boost::mpl::vector1<
		sge::sprite::config::with_texture<
			sge::sprite::config::texture_level_count<
				1u
			>,
			sge::sprite::config::texture_coordinates::automatic,
			sge::sprite::config::texture_ownership::reference
		>
	>
>
image_sprite_choices;

}
}
}

#endif
