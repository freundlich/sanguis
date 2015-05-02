#ifndef SANGUIS_SERVER_AI_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CONTEXT_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/optional_pos_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/pathing/optional_target_fwd.hpp>
#include <sanguis/server/ai/pathing/optional_trail.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/warn_unused_result.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	explicit
	context(
		sanguis::server::entities::with_ai &
	);

	~context();

	bool
	path_find(
		sanguis::creator::pos
	)
	FCPPT_PP_WARN_UNUSED_RESULT;

	void
	clear_path();

	sanguis::creator::optional_pos const
	destination() const;

	sanguis::server::ai::pathing::optional_target const
	continue_path();

	sanguis::creator::grid const &
	grid() const;

	sanguis::server::entities::with_ai &
	me();

	sanguis::server::entities::with_ai const &
	me() const;
private:
	sanguis::server::entities::with_ai &me_;

	sanguis::server::ai::pathing::optional_trail trail_;
};

}
}
}

#endif
