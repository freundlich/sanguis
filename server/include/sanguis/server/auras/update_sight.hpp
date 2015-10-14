#ifndef SANGUIS_SERVER_AURAS_UPDATE_SIGHT_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_UPDATE_SIGHT_HPP_INCLUDED

#include <sanguis/optional_aura_type_fwd.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
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

	~update_sight()
	override;
private:
	sanguis::optional_aura_type
	type() const
	override;

	void
	enter(
		sanguis::server::entities::with_body &,
		sanguis::collision::world::created
	)
	override;

	void
	leave(
		sanguis::server::entities::with_body &
	)
	override;

	sanguis::server::add_sight_callback const add_;

	sanguis::server::remove_sight_callback const remove_;
};

}
}
}

#endif
