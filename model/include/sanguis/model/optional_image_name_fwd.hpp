#ifndef SANGUIS_MODEL_OPTIONAL_IMAGE_NAME_FWD_HPP_INCLUDED
#define SANGUIS_MODEL_OPTIONAL_IMAGE_NAME_FWD_HPP_INCLUDED

#include <sanguis/model/image_name_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace model
{

typedef
fcppt::optional<
	sanguis::model::image_name
>
optional_image_name;

}
}

#endif