#ifndef SANGUIS_SERVER_AI_BEHAVIOR_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/ai/behavior/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace behavior
{

using
base_unique_ptr
=
fcppt::unique_ptr<
	sanguis::server::ai::behavior::base
>;

}
}
}
}

#endif
