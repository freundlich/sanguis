#ifndef SANGUIS_TOOLS_ANIMATIONS_CONST_OPTIONAL_IMAGE_FILE_REF_FWD_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_CONST_OPTIONAL_IMAGE_FILE_REF_FWD_HPP_INCLUDED

#include <fcppt/optional_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{

typedef
fcppt::optional<
	QImage const &
>
const_optional_image_file_ref;

}
}
}

#endif
