#include "status.hpp"

sanguis::server::perks::status::status(
	perk_type::type const type_)
:
	type_(type_),
	chosen_(false)
{}
	
bool
sanguis::server::perks::status::chosen() const
{
	return chosen_;
}

void
sanguis::server::perks::status::choose()
{
	chosen_ = true;
}

sanguis::perk_type::type
sanguis::server::perks::status::type() const
{
	return type_;
}
