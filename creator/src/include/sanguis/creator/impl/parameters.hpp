#ifndef SANGUIS_CREATOR_IMPL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/impl/parameters_fwd.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		sanguis::creator::impl::random::generator &,
		sanguis::creator::spawn_boss,
		sanguis::creator::opening_count_array
	);

	sanguis::creator::impl::random::generator &
	randgen() const;

	sanguis::creator::spawn_boss const
	spawn_boss() const;

	sanguis::creator::opening_count_array const
	opening_count_array() const;
private:
	sanguis::creator::impl::random::generator &randgen_;

	sanguis::creator::spawn_boss const spawn_boss_;

	sanguis::creator::opening_count_array const opening_count_array_;
};

}
}
}

#endif