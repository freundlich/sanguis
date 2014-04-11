#ifndef SANGUIS_SERVER_AURAS_UPDATE_SIGHT_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_UPDATE_SIGHT_HPP_INCLUDED

#include <sanguis/optional_aura_type_fwd.hpp>
#include <sanguis/collision/world/group_field_fwd.hpp>
#include <sanguis/server/add_sight_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_sight_callback.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

class update_sight
:
	public sanguis::server::auras::aura
{
	FCPPT_NONCOPYABLE(
		update_sight
	);
public:
	update_sight(
		sanguis::server::radius,
		sanguis::server::add_sight_callback const &,
		sanguis::server::remove_sight_callback const &
	);

	~update_sight();
private:
	sanguis::optional_aura_type const
	type() const
	override;

	sanguis::collision::world::group_field const
	collision_groups() const;

	void
	enter(
		sanguis::server::entities::with_body &
	);

	void
	leave(
		sanguis::server::entities::with_body &
	);

	sanguis::server::add_sight_callback const add_;

	sanguis::server::remove_sight_callback const remove_;
};

}
}
}

#endif