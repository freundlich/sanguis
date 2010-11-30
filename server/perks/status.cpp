#include "status.hpp"
#include <fcppt/assert.hpp>
#include <limits>

sanguis::server::perks::status::status()
:
	type_(perk_type::size),
	required_player_level_(0),
	required_parent_level_(0),
	level_(
		std::numeric_limits<
			level_type
		>::max()
	)
{}

sanguis::server::perks::status::status(
	perk_type::type const _type,
	level_type const _required_player_level,
	level_type const _required_parent_level
)
:
	type_(_type),
	required_player_level_(_required_player_level),
	required_parent_level_(_required_parent_level),
	level_(0)
{}
	
void
sanguis::server::perks::status::choose()
{
	FCPPT_ASSERT(type() != perk_type::size);
	++level_;
}

sanguis::server::perks::level_type
sanguis::server::perks::status::required_player_level() const
{
	return required_player_level_;
}

sanguis::server::perks::level_type
sanguis::server::perks::status::required_parent_level() const
{
	return required_parent_level_;
}
sanguis::server::perks::level_type
sanguis::server::perks::status::level() const
{
	return level_;
}

sanguis::perk_type::type
sanguis::server::perks::status::type() const
{
	return type_;
}
