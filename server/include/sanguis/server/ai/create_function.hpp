#ifndef SANGUIS_SERVER_AI_CREATE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CREATE_FUNCTION_HPP_INCLUDED

#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/tree/base_unique_ptr.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

typedef
fcppt::function<
	sanguis::server::ai::tree::base_unique_ptr (
		sanguis::server::ai::context &
	)
>
create_function;

}
}
}

#endif
