#ifndef SANGUIS_CLIENT_LOAD_MODEL_MAKE_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_MAKE_TEXTURE_HPP_INCLUDED

#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sge/texture/part_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

sge::texture::part const &
make_texture(
	sanguis::client::load::model::global_parameters const &
);

}
}
}
}

#endif
