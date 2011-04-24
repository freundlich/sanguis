#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED

#include "own.hpp"
#include "../particle/base_ptr.hpp"
#include "../particle/container.hpp"
#include "../particle/property_map.hpp"
#include "../particle/properties_fwd.hpp"
#include "../particle/particle_type.hpp"
#include "../sprite/particle/system.hpp"
#include "../sprite/center.hpp"
#include "../aoe.hpp"
#include "../../../load/model/collection_fwd.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class explosion
:
	public entities::own
{
	FCPPT_NONCOPYABLE(
		explosion
	);
public:
	explosion(
		sprite::particle::system &,
		load::model::collection const &,
		sprite::center const &,
		draw2d::aoe
	);

	~explosion();
private:
	// base overrides
	
	void
	update(
		time_type
	);

	bool
	may_be_removed() const;

	particle::base_ptr
	generate_explosion();

	particle::base_ptr
	generate_particle(
		particle::particle_type::type
	);

	particle::properties const &
	properties(
		particle::particle_type::type const t
	) const;
	
	sprite::particle::system &particle_system_;

	load::model::collection const &model_collection_;

	particle::container particles_;

	particle::property_map properties_;

	sprite::center const center_;

	draw2d::aoe aoe_;

	bool ended_;
};

}
}
}
}

#endif
