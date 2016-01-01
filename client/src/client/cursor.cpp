#include <sanguis/client/cursor.hpp>
#include <sanguis/client/optional_cursor_area.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/cursor_hotspot.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_signed.hpp>
#include <fcppt/optional/map.hpp>


sanguis::client::cursor::cursor(
	sge::renderer::device::ffp &_renderer,
	sge::input::cursor::object &_cursor,
	sanguis::client::load::resource::textures const &_textures
)
:
	texture_(
		_textures.load(
			sanguis::client::load::resource::texture_identifier(
				FCPPT_TEXT("cursor")
			)
		)
	),
	input_cursor_(
		_cursor
	),
	cursor_{
		_renderer,
		_cursor,
		texture_,
		sge::systems::cursor_hotspot{
			fcppt::math::vector::structure_cast<
				sge::systems::cursor_hotspot::value_type,
				fcppt::cast::size_fun
			>(
				fcppt::math::dim::to_vector(
					texture_.size()
					/
					fcppt::literal<
						sge::renderer::size_type
					>(
						2
					)
				)
			)
		}
	}
{
}

sanguis::client::cursor::~cursor()
{
}

void
sanguis::client::cursor::draw(
	sge::renderer::context::ffp &_context
)
{
	cursor_.draw(
		_context
	);
}

sanguis::client::optional_cursor_area
sanguis::client::cursor::area() const
{
	return
		fcppt::optional::map(
			input_cursor_.position(),
			[
				this
			](
				sge::input::cursor::position const _pos
			)
			{
				return
					sanguis::client::cursor_area(
						_pos
						-
						fcppt::math::vector::structure_cast<
							sanguis::client::cursor_area::vector,
							fcppt::cast::size_fun
						>(
							fcppt::math::vector::to_signed(
								cursor_.hotspot().get()
							)
						),
						fcppt::math::dim::structure_cast<
							sanguis::client::cursor_area::dim,
							fcppt::cast::size_fun
						>(
							fcppt::math::dim::to_signed(
								texture_.size()
							)
						)
					);
			}
		);
}
