#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sanguis/creator/geometry/solidity.hpp>
#include <sanguis/server/world/create_static_body.hpp>
#include <sanguis/server/world/triangle_traits/access_element.hpp>
#include <sanguis/server/world/triangle_traits/insert_result.hpp>
#include <sanguis/server/world/triangle_traits/scalar.hpp>
#include <sanguis/server/world/triangle_traits/tag.hpp>
#include <sge/projectile/vector2.hpp>
#include <sge/projectile/body/angular_velocity.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/body/object_unique_ptr.hpp>
#include <sge/projectile/body/parameters.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/solidity/solid.hpp>
#include <sge/projectile/shape/triangle_mesh.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>
#include <sge/projectile/triangulation/default_tag.hpp>
#include <sge/projectile/triangulation/triangulate.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::projectile::body::object_unique_ptr
sanguis::server::world::create_static_body(
	sanguis::creator::geometry::shape_container const &_shapes
)
{
	sge::projectile::shape::triangle_sequence triangles;

	for(
		auto const &shape : _shapes
	)
	{
		if(
			shape.solidity()
			!=
			sanguis::creator::geometry::solidity::solid
		)
			continue;

		sge::projectile::shape::triangle_sequence const new_triangles(
			sge::projectile::triangulation::triangulate<
				sanguis::server::world::triangle_traits::tag,
				sge::projectile::shape::triangle_sequence
			>(
				shape.polygon(),
				0
			)
		);

		triangles.insert(
			triangles.end(),
			new_triangles.begin(),
			new_triangles.end()
		);
	}

	return
		triangles.empty()
		?
			sge::projectile::body::object_unique_ptr()
		:
			fcppt::make_unique_ptr<
				sge::projectile::body::object
			>(
				sge::projectile::body::parameters(
					sge::projectile::body::position(
						sge::projectile::vector2::null()
					),
					sge::projectile::body::linear_velocity(
						sge::projectile::vector2::null()
					),
					sge::projectile::body::angular_velocity(
						0.f
					),
					fcppt::make_shared_ptr<
						sge::projectile::shape::triangle_mesh
					>(
						triangles
					),
					sge::projectile::body::rotation(
						0.f
					),
					sge::projectile::body::solidity::static_(),
					sge::projectile::body::user_data()
				)
			);
}
