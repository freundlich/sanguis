#ifndef SANGUIS_SERVER_AI_GO_CLOSE_TO_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_GO_CLOSE_TO_TARGET_HPP_INCLUDED

#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/speed_factor_fwd.hpp>
#include <sanguis/server/ai/target_fwd.hpp>
#include <fcppt/preprocessor/warn_unused_result.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

bool
go_close_to_target(
	sanguis::server::ai::context &,
	sanguis::server::ai::target,
	sanguis::server::ai::speed_factor
)
FCPPT_PP_WARN_UNUSED_RESULT;

}
}
}

#endif
