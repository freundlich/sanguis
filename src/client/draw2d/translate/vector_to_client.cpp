#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/translate/vector_to_client.hpp>
#include <sanguis/client/draw2d/translate/scalar_to_client.hpp>
#include <sanguis/messages/types/vector2.hpp>
#include <fcppt/math/map.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::client::draw2d::vector2 const
sanguis::client::draw2d::translate::vector_to_client(
	sanguis::messages::types::vector2 const &_vec
)
{
	return
		fcppt::math::vector::structure_cast<
			sanguis::client::draw2d::vector2
		>(
			fcppt::math::map<
				sanguis::client::draw2d::vector2
			>(
				_vec,
				&sanguis::client::draw2d::translate::scalar_to_client
			)
		);
}
