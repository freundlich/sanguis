#include "shoot.hpp"

sanguis::server::weapons::events::shoot::shoot(
	entities::entity_with_weapon &from_,
	pos_type const &to_)
:
	from_(from_),
	to_(to_)
{}
	
sanguis::server::entities::entity_with_weapon &
sanguis::server::weapons::events::shoot::from() const
{
	return from_;
}

sanguis::server::pos_type const &
sanguis::server::weapons::events::shoot::to() const
{
	return to_;
}