#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/destructible.hpp>
#include <sanguis/load/model/destructible_path.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/generate_destructibles.hpp>
#include <sanguis/server/world/insert_pair_container.hpp>
#include <sanguis/server/world/make_destructible.hpp>
#include <sanguis/server/world/place_callback.hpp>
#include <sanguis/server/world/place_multiple.hpp>


sanguis::server::world::insert_pair_container
sanguis::server::world::generate_destructibles(
	sanguis::random_generator &_random_generator,
	sanguis::creator::destructible const &_destructible,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::world::difficulty const _difficulty
)
{
	return
		sanguis::server::world::place_multiple(
			_random_generator,
			sanguis::server::world::place_callback(
				[
					_destructible,
					&_load_context,
					_difficulty
				]
				{
					return
						sanguis::server::world::make_destructible(
							_destructible.type(),
							_load_context,
							_difficulty
						);
				}
			),
			_destructible.pos().get(),
			_load_context.model_size(
				sanguis::load::model::destructible_path(
					_destructible.type()
				)
			)
		);
}
