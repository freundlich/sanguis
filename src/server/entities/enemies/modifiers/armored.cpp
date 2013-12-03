#include <sanguis/random_generator.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/type_to_string.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/armored.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_enum.hpp>


sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::modifiers::armored(
	sanguis::server::entities::enemies::parameters &_parameters,
	sanguis::server::entities::enemies::modifiers::parameters const &_modifier_parameters
)
{
	auto uniform_enum(
		fcppt::random::distribution::make_basic(
			fcppt::random::distribution::parameters::make_uniform_enum<
				sanguis::server::damage::type
			>()
		)
	);

	sanguis::server::damage::type const damage_type(
		uniform_enum(
			_modifier_parameters.random_generator()
		)
	);

	_parameters.armor_element(
		damage_type,
		sanguis::server::damage::unit(
			0.9f
		)
	);

	return
		sanguis::server::entities::enemies::attribute(
			sanguis::server::damage::type_to_string(
				damage_type
			)
			+
			FCPPT_TEXT(" resistant")
		);
}
