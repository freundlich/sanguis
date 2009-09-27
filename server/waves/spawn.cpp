#include "spawn.hpp"
#include "../entities/enemies/factory.hpp"
#include "../entities/base.hpp"
#include "../entities/insert_parameters.hpp"
#include "../environment/object.hpp"
#include "../../random.hpp"
#include "../../angle_to_vector.hpp"
#include "../../resolution.hpp"
#include <sge/math/twopi.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <tr1/random>
#include <algorithm>

void
sanguis::server::waves::spawn(
	environment::object_ptr const env,
	environment::load_context_ptr const load_context,
	enemy_type::type const etype
)
{
	// TODO: put this randomizer somewhere else!
	
	typedef std::tr1::uniform_real<
		space_unit
	> uniform_su;

	typedef std::tr1::variate_generator<
		rand_gen_type,
		uniform_su
	> rng_type;

	static rng_type rng(
		create_seeded_randgen(),
		uniform_su(
			static_cast<space_unit>(0),
			sge::math::twopi<space_unit>()
		));

	sge::renderer::screen_size const res(
		resolution());

	space_unit const
		rand_angle(rng()),
		radius(
			static_cast<space_unit>(
				std::max(
					res.w(),
					res.h()))
			/ static_cast<space_unit>(2)),
		scale(static_cast<space_unit>(1.5)),
		angle(static_cast<space_unit>(0)
	);
	
	pos_type const
		screen_center(
			pos_type(
				static_cast<space_unit>(res.w()),
				static_cast<space_unit>(res.h()))
			/ static_cast<space_unit>(2)),
		center(
			scale * radius * angle_to_vector(rand_angle)),
		pos(
			center + screen_center);

	env->insert(
		entities::enemies::create(
			etype,
			load_context
		),
		entities::insert_parameters(
			pos,
			angle
		)
	);
}
