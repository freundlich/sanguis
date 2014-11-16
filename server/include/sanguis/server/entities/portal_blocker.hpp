#ifndef SANGUIS_SERVER_ENTITIES_PORTAL_BLOCKER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PORTAL_BLOCKER_HPP_INCLUDED

#include <sanguis/server/entities/doodad.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class portal_blocker
:
	public sanguis::server::entities::doodad
{
	FCPPT_NONCOPYABLE(
		portal_blocker
	);
public:
	explicit
	portal_blocker(
		sanguis::server::environment::load_context &
	);

	~portal_blocker()
	override;
};

}
}
}

#endif