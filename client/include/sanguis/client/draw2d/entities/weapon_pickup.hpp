#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WEAPON_PICKUP_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WEAPON_PICKUP_HPP_INCLUDED

#include <sanguis/weapon_description.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class weapon_pickup
:
	public sanguis::client::draw2d::entities::model::object
{
	FCPPT_NONCOPYABLE(
		weapon_pickup
	);
public:
	weapon_pickup(
		sanguis::client::draw2d::entities::model::load_parameters const &,
		sanguis::weapon_description const &
	);

	~weapon_pickup()
	override;
private:
	sanguis::client::draw2d::entities::hover::optional_info
	hover() const
	override;

	sanguis::weapon_description const weapon_description_;
};

}
}
}
}

#endif