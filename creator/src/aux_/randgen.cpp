#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/aux_/randgen.hpp>
#include <sanguis/creator/aux_/rand_value.hpp>
#include <fcppt/random/generator/minstd_rand_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


sanguis::creator::aux_::randgen::randgen(
	sanguis::creator::seed const &_seed
)
:
	generator_(
		generator_type::seed(
			_seed.get()
		)
	)
{
	static_assert(
		std::numeric_limits<
			sanguis::creator::aux_::rand_value
		>::min()
		==
		generator_type::min(),
		"min does not match"
	);

	static_assert(
		std::numeric_limits<
			sanguis::creator::aux_::rand_value
		>::max()
		==
		generator_type::max(),
		"max does not match"
	);
}

sanguis::creator::aux_::randgen::~randgen()
{
}

sanguis::creator::aux_::randgen::result_type
sanguis::creator::aux_::randgen::operator()()
{
	return
		static_cast<
			sanguis::creator::aux_::randgen::result_type
		>(
			generator_()
		);
}

sanguis::creator::aux_::randgen::result_type
sanguis::creator::aux_::randgen::min()
{
	return
		static_cast<
			sanguis::creator::aux_::rand_value
		>(
			generator_type::min()
		);
}

sanguis::creator::aux_::randgen::result_type
sanguis::creator::aux_::randgen::max()
{
	return
		static_cast<
			sanguis::creator::aux_::rand_value
		>(
			generator_type::max()
		);
}
