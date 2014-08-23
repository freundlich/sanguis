#ifndef SANGUIS_SERVER_AI_TREE_MAKE_LEAF_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_MAKE_LEAF_HPP_INCLUDED

#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/ai/tree/base_unique_ptr.hpp>
#include <sanguis/server/ai/tree/leaf.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace tree
{

template<
	typename Behavior,
	typename... Args
>
sanguis::server::ai::tree::base_unique_ptr
make_leaf(
	Args &&... _args
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::ai::tree::leaf
		>(
			fcppt::make_unique_ptr<
				Behavior
			>(
				std::forward<
					Args
				>(
					_args
				)...
			)
		);
}

}
}
}
}

#endif
