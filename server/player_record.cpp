#include "player_record.hpp"

sanguis::server::player_record::player_record(
	sge::string const &name_,
	exp_type const exp_)
:
	name_(name_),
	exp_(exp_)
{}
	
sge::string const &
sanguis::server::player_record::name() const
{
	return name_;
}

sanguis::server::exp_type
sanguis::server::player_record::exp() const
{
	return exp_;
}