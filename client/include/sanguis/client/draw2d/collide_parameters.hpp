#ifndef SANGUIS_CLIENT_DRAW2D_COLLIDE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_COLLIDE_PARAMETERS_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/collide_parameters_fwd.hpp>
#include <sanguis/client/draw2d/fradius.hpp>
#include <sanguis/client/draw2d/speed.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{

class collide_parameters
{
	FCPPT_NONASSIGNABLE(
		collide_parameters
	);
public:
	collide_parameters(
		sanguis::duration,
		sanguis::client::draw2d::center,
		sanguis::client::draw2d::speed,
		sanguis::client::draw2d::fradius
	);

	sanguis::duration const
	duration() const;

	sanguis::client::draw2d::center const
	center() const;

	sanguis::client::draw2d::speed const
	speed() const;

	sanguis::client::draw2d::fradius const
	radius() const;
private:
	sanguis::duration const duration_;

	sanguis::client::draw2d::center const center_;

	sanguis::client::draw2d::speed const speed_;

	sanguis::client::draw2d::fradius const radius_;
};

}
}
}

#endif
