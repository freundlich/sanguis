#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info.hpp>


sanguis::client::draw2d::entities::base::base()
{
}

void
sanguis::client::draw2d::entities::base::die()
{
	this->on_die();
}

bool
sanguis::client::draw2d::entities::base::may_be_removed() const
{
	return
		this->is_decayed();
}

sanguis::client::draw2d::entities::hover::optional_info
sanguis::client::draw2d::entities::base::hover() const
{
	return
		sanguis::client::draw2d::entities::hover::optional_info();
}

sanguis::client::draw2d::entities::base::~base()
{
}
