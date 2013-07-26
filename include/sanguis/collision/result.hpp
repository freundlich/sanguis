#ifndef SANGUIS_COLLISION_RESULT_HPP_INCLUDED
#define SANGUIS_COLLISION_RESULT_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/result_fwd.hpp>
#include <sanguis/collision/speed.hpp>


namespace sanguis
{
namespace collision
{

class result
{
public:
	result(
		sanguis::collision::speed const &,
		sanguis::collision::center const &
	);

	sanguis::collision::speed const &
	speed() const;

	sanguis::collision::center const &
	center() const;
private:
	sanguis::collision::speed speed_;

	sanguis::collision::center center_;
};

}
}

#endif