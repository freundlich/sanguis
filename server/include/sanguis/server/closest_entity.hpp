#ifndef SANGUIS_SERVER_CLOSEST_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_CLOSEST_ENTITY_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/collision/distance_entity_entity.hpp>
#include <sanguis/server/entities/base.hpp>
#include <fcppt/const.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/optional_impl.hpp>


namespace sanguis
{
namespace server
{

template<
	typename Container,
	typename Predicate
>
fcppt::optional<
	typename
	Container::value_type::type &
>
closest_entity(
	sanguis::server::entities::base const &_ref,
	Container const &_entities,
	Predicate const _predicate
)
{
	typedef
	fcppt::optional<
		typename
		Container::value_type::type &
	>
	result_type;

	result_type ret;

	typedef
	fcppt::optional<
		sanguis::server::space_unit
	>
	optional_space_unit;

	optional_space_unit distance;

	for(
		auto const entity
		:
		_entities
	)
	{
		sanguis::server::space_unit const new_distance(
			sanguis::server::collision::distance_entity_entity(
				_ref,
				entity.get()
			)
		);

		if(
			_predicate(
				entity.get()
			)
			&&
			fcppt::maybe(
				distance,
				fcppt::const_(
					true
				),
				[
					new_distance
				](
					sanguis::server::space_unit const _old_distance
				)
				{
					return
						new_distance
						<
						_old_distance;
				}
			)
		)
		{
			distance =
				optional_space_unit(
					new_distance
				);

			ret =
				result_type(
					entity.get()
				);
		}
	}

	return
		ret;
}

}
}

#endif
