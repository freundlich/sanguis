#include <sanguis/creator/count.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux_/closest_empty.hpp>
#include <sanguis/creator/aux_/enemy_type_container.hpp>
#include <sanguis/creator/aux_/optional_pos.hpp>
#include <sanguis/creator/aux_/place_spawners.hpp>
#include <sanguis/creator/aux_/random/generator.hpp>
#include <sanguis/creator/aux_/random/uniform_int_wrapper_impl.hpp>
#include <sanguis/creator/aux_/random/uniform_size.hpp>
#include <sanguis/creator/aux_/random/uniform_size_variate.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_indices_advanced.hpp>


sanguis::creator::spawn_container
sanguis::creator::aux_::place_spawners(
	sanguis::creator::grid &_grid,
	sanguis::creator::count const _spawner_count,
	sanguis::creator::aux_::random::generator &_generator,
	sanguis::creator::aux_::enemy_type_container const &_enemy_types
)
{
	auto const boundary(
		[](
			sanguis::creator::size_type const _sz
		)
		{
			FCPPT_ASSERT_PRE(
				_sz
				>=
				3u
			);

			return
				sanguis::creator::aux_::random::uniform_size{
					sanguis::creator::aux_::random::uniform_size::param_type::min{
						1u
					},
					sanguis::creator::aux_::random::uniform_size::param_type::max{
						_sz - 2
					}
				};
		}
	);

	sanguis::creator::aux_::random::uniform_size_variate random_x{
		_generator,
		boundary(
			_grid.size().w()
		)
	};

	sanguis::creator::aux_::random::uniform_size_variate random_y{
		_generator,
		boundary(
			_grid.size().h()
		)
	};

	auto random_monster(
		fcppt::random::distribution::make_basic(
			fcppt::random::distribution::parameters::make_uniform_indices_advanced<
				sanguis::creator::aux_::random::uniform_int_wrapper
			>(
				_enemy_types
			)
		)
	);

	sanguis::creator::spawn_container
	spawners;

	sanguis::creator::spawn_container::size_type
	current_spawners{
		0u
	};

	sanguis::creator::count iterations{
		0u
	};

	while(
		current_spawners
		<
		_spawner_count
	)
	{
		if(
			++iterations
			>
			_spawner_count * 5
		)
			throw sanguis::creator::exception{
				FCPPT_TEXT(
					"Could not place spawners, giving up."
				)
			};

		sanguis::creator::aux_::optional_pos const
		candidate{
			sanguis::creator::aux_::closest_empty(
				_grid,
				sanguis::creator::pos{
					random_x(),
					random_y()
				}
			)
		};

		if(
			!candidate
		)
			continue;

		_grid
		[
			*candidate
		] =
			sanguis::creator::tile::spawner;

		spawners.push_back(
			sanguis::creator::spawn{
				sanguis::creator::spawn_pos{
					*candidate
				},
				_enemy_types[
					random_monster(
						_generator
					)
				],
				sanguis::creator::spawn_type::spawner
			}
		);

		++current_spawners;
	}

	return
		spawners;
}


