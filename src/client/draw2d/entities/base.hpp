#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BASE_HPP_INCLUDED

#include "../sprite/point.hpp"
#include "../sprite/dim.hpp"
#include "../../../time_type.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual void
	update(
		time_type
	) = 0;

	void
	decay();

	bool
	may_be_removed() const;
	
	virtual void
	pos(
		sprite::point const &
	) = 0;

	virtual void
	dim(
		sprite::dim const &
	) = 0;

	virtual sprite::point const
	center() const = 0;

	virtual ~base();
private:
	virtual void
	on_decay();

	virtual bool
	is_decayed() const;

	bool removed_;
};

}
}
}
}

#endif
