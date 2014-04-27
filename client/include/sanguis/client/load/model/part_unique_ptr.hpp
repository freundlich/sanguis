#ifndef SANGUIS_CLIENT_LOAD_MODEL_PART_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_PART_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/load/model/part_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

typedef
std::unique_ptr<
	sanguis::client::load::model::part
>
part_unique_ptr;

}
}
}
}

#endif