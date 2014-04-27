#ifndef SANGUIS_SERVER_WEAPONS_FACTORY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_FACTORY_PARAMETERS_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/factory/parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace factory
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::weapon_type,
		sanguis::server::entities::enemies::difficulty
	);

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::random_generator &
	random_generator() const;

	sanguis::weapon_type const
	weapon_type() const;

	sanguis::server::entities::enemies::difficulty const
	difficulty() const;
private:
	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::weapon_type const weapon_type_;

	sanguis::server::entities::enemies::difficulty const difficulty_;
};

}
}
}
}

#endif