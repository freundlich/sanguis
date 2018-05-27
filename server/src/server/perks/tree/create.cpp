#include <sanguis/perk_type.hpp>
#include <sanguis/server/perks/tree/container.hpp>
#include <sanguis/server/perks/tree/create.hpp>
#include <sanguis/server/perks/tree/max_level.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/required_parent_level.hpp>
#include <sanguis/server/perks/tree/required_player_level.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <fcppt/container/make.hpp>


sanguis::server::perks::tree::container
sanguis::server::perks::tree::create()
{
	return
		fcppt::container::make<
			sanguis::server::perks::tree::container
		>(
			sanguis::server::perks::tree::object(
				sanguis::server::perks::tree::status(
					sanguis::perk_type::choleric,
					sanguis::server::perks::tree::required_player_level(
						2u
					),
					sanguis::server::perks::tree::required_parent_level(
						0u
					),
					sanguis::server::perks::tree::max_level(
						10u
					)
				)
			),
			sanguis::server::perks::tree::object(
				sanguis::server::perks::tree::status(
					sanguis::perk_type::ias,
					sanguis::server::perks::tree::required_player_level(
						0u
					),
					sanguis::server::perks::tree::required_parent_level(
						0u
					),
					sanguis::server::perks::tree::max_level(
						8U
					)
				)
			),
			sanguis::server::perks::tree::object(
				sanguis::server::perks::tree::status(
					sanguis::perk_type::ims,
					sanguis::server::perks::tree::required_player_level(
						0u
					),
					sanguis::server::perks::tree::required_parent_level(
						0u
					),
					sanguis::server::perks::tree::max_level(
						7u
					)
				)
			),
			sanguis::server::perks::tree::object(
				sanguis::server::perks::tree::status(
					sanguis::perk_type::irs,
					sanguis::server::perks::tree::required_player_level(
						0u
					),
					sanguis::server::perks::tree::required_parent_level(
						0u
					),
					sanguis::server::perks::tree::max_level(
						4u
					)
				)
			),
			sanguis::server::perks::tree::object(
				sanguis::server::perks::tree::status(
					sanguis::perk_type::health,
					sanguis::server::perks::tree::required_player_level(
						0u
					),
					sanguis::server::perks::tree::required_parent_level(
						0u
					),
					sanguis::server::perks::tree::max_level(
						10u
					)
				)
			),
			sanguis::server::perks::tree::object(
				sanguis::server::perks::tree::status(
					sanguis::perk_type::fire_damage,
					sanguis::server::perks::tree::required_player_level(
						0u
					),
					sanguis::server::perks::tree::required_parent_level(
						0u
					),
					sanguis::server::perks::tree::max_level(
						10u
					)
				)
			),
			sanguis::server::perks::tree::object(
				sanguis::server::perks::tree::status(
					sanguis::perk_type::piercing_damage,
					sanguis::server::perks::tree::required_player_level(
						0u
					),
					sanguis::server::perks::tree::required_parent_level(
						0u
					),
					sanguis::server::perks::tree::max_level(
						10u
					)
				)
			)
		);
}
