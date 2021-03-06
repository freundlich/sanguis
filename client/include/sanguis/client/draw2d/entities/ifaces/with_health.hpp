#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_HEALTH_HPP_INCLUDED

#include <sanguis/client/health.hpp>
#include <sanguis/client/max_health.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace ifaces
{

class with_health
{
	FCPPT_NONMOVABLE(
		with_health
	);
protected:
	with_health();

	virtual
	~with_health();
public:
	virtual
	void
	health(
		sanguis::client::health
	) = 0;

	virtual
	void
	max_health(
		sanguis::client::max_health
	) = 0;
};

}
}
}
}
}

#endif
