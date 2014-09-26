#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/aux_/cross2.hpp>
#include <sanguis/collision/aux_/is_null.hpp>
#include <sanguis/collision/aux_/line_line_intersect.hpp>
#include <sanguis/collision/aux_/line_segment.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


bool
sanguis::collision::aux_::line_line_intersect(
	sanguis::collision::aux_::line_segment const _line1,
	sanguis::collision::aux_::line_segment const _line2
)
{
	sanguis::collision::unit const dot_perp(
		sanguis::collision::aux_::cross2(
			_line1.dir().get(),
			_line2.dir().get()
		)
	);

	if(
		sanguis::collision::aux_::is_null(
			dot_perp
		)
	)
		return
			false;

	sanguis::collision::vector2 const c(
		_line2.pos().get()
		-
		_line1.pos().get()
	);

	sanguis::collision::unit const t(
		sanguis::collision::aux_::cross2(
			c,
			_line2.dir().get()
		)
		/
		dot_perp
	);

	sanguis::collision::unit const one(
		fcppt::literal<
			sanguis::collision::unit
		>(
			1
		)
	);

	sanguis::collision::unit const zero(
		fcppt::literal<
			sanguis::collision::unit
		>(
			0
		)
	);

	if(
		t < zero || t > one
	)
		return
			false;

	sanguis::collision::unit const u(
		sanguis::collision::aux_::cross2(
			c,
			_line1.dir().get()
		)
		/
		dot_perp
	);

	return
		u >= zero && u <= one;
}
