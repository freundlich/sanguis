#ifndef SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED

#include <sanguis/optional_aura_type_fwd.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/group_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <sanguis/server/collision/ghost_unique_ptr.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

class aura
:
	private sanguis::server::collision::ghost_base
{
	FCPPT_NONCOPYABLE(
		aura
	);
public:
	~aura()
	override;

	sanguis::server::collision::ghost_unique_ptr
	create_ghost();

	virtual
	sanguis::optional_aura_type const
	type() const = 0;
protected:
	aura(
		sanguis::server::radius,
		sanguis::server::team,
		sanguis::server::auras::influence
	);
private:
	virtual
	sanguis::collision::world::group
	collision_group() const;

	boost::logic::tribool const
	can_collide_with(
		sanguis::collision::world::body_base const &
	) const
	override;

	void
	body_enter(
		sanguis::collision::world::body_base &
	)
	override;

	void
	body_exit(
		sanguis::collision::world::body_base &
	)
	override;

	virtual
	void
	enter(
		sanguis::server::entities::with_body &
	) = 0;

	virtual
	void
	leave(
		sanguis::server::entities::with_body &
	) = 0;

	sanguis::server::radius const radius_;

	sanguis::server::team const team_;

	sanguis::server::auras::influence const influence_;
};

}
}
}

#endif
