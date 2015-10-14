#include <sanguis/creator/optional_pos.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/pathing/find_target.hpp>
#include <sanguis/server/ai/pathing/optional_target.hpp>
#include <sanguis/server/ai/pathing/optional_trail.hpp>
#include <sanguis/server/ai/pathing/simplify.hpp>
#include <sanguis/server/ai/pathing/start.hpp>
#include <sanguis/server/ai/pathing/target.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <sanguis/server/ai/pathing/update_trail.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/maybe_front.hpp>


sanguis::server::ai::context::context(
	sanguis::server::entities::with_ai &_me
)
:
	me_(
		_me
	),
	trail_()
{
}

sanguis::server::ai::context::~context()
{
}

bool
sanguis::server::ai::context::path_find(
	sanguis::creator::pos const _pos
)
{
	trail_ =
		fcppt::optional_bind_construct(
			sanguis::server::ai::pathing::find_target(
				this->grid(),
				sanguis::server::ai::pathing::start(
					sanguis::server::world::center_to_grid_pos(
						this->me().center()
					)
				),
				sanguis::server::ai::pathing::target(
					_pos
				)
			),
			[
				this
			](
				sanguis::server::ai::pathing::trail const &_trail
			)
			{
				return
					sanguis::server::ai::pathing::simplify(
						_trail,
						this->grid()
					);
			}
		);

	return
		trail_.has_value();
}

void
sanguis::server::ai::context::clear_path()
{
	trail_ =
		sanguis::server::ai::pathing::optional_trail();
}

sanguis::creator::optional_pos
sanguis::server::ai::context::destination() const
{
	return
		fcppt::optional_bind(
			trail_,
			[](
				sanguis::server::ai::pathing::trail const &_trail
			)
			{
				return
					sanguis::creator::optional_pos{
						fcppt::container::maybe_front(
							_trail
						)
					};
			}
		);
}

sanguis::server::ai::pathing::optional_target
sanguis::server::ai::context::continue_path()
{
	return
		fcppt::optional_bind(
			trail_,
			[
				this
			](
				sanguis::server::ai::pathing::trail &_trail
			)
			{
				return
					sanguis::server::ai::pathing::update_trail(
						_trail,
						this->grid(),
						this->me()
					);
			}
		);
}

sanguis::creator::grid const &
sanguis::server::ai::context::grid() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			this->me().environment()
		).grid();
}

sanguis::server::entities::with_ai &
sanguis::server::ai::context::me()
{
	return
		me_;
}

sanguis::server::entities::with_ai const &
sanguis::server::ai::context::me() const
{
	return
		me_;
}
