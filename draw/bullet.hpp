#ifndef SANGUIS_DRAW_BULLET_HPP_INCLUDED
#define SANGUIS_DRAW_BULLET_HPP_INCLUDED

#include "model.hpp"
#include <sge/sprite/types.hpp>
#include <sge/string.hpp>
#include <boost/optional.hpp>

namespace sanguis
{
namespace draw
{

class bullet : public model {
public:
	bullet(
		entity_id id,
		system &,
		sge::string const &name);
private:
	void update(time_type);
	boost::optional<sge::sprite::point> origin;
};

}
}

#endif
