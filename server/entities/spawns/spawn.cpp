#include "spawn.hpp"
#include "../../environment/object.hpp"
#include "../../waves/spawn.hpp"

void
sanguis::server::entities::spawns::spawn::unregister(
	entities::base &
)
{
}

sanguis::server::entities::spawns::spawn::~spawn()
{
}

sanguis::server::entities::spawns::spawn::spawn(
	enemy_type::type const enemy_type_
)
:
	enemy_type_(enemy_type_)
{}

sanguis::server::space_unit
sanguis::server::entities::spawns::spawn::radius() const
{
	return static_cast<space_unit>(1); // TODO!
}

sanguis::entity_type::type
sanguis::server::entities::spawns::spawn::type() const
{
	return entity_type::spawn;
}

sanguis::server::team::type
sanguis::server::entities::spawns::spawn::team() const
{
	return server::team::monsters;
}

void
sanguis::server::entities::spawns::spawn::on_update(
	time_type const time_
)
{
	if(
		size_type const count_ =
			may_spawn(
				time_
			)
	)
	{
		for(
			size_type i = 0;
			i < count_;
			++i
		)
			waves::spawn(
				environment(),
				environment()->load_context(),
				enemy_type_,
				link()
			);

		add_count(
			count_
		);
	}
}
