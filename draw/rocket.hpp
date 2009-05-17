#ifndef SANGUIS_DRAW_ROCKET_HPP_INCLUDED
#define SANGUIS_DRAW_ROCKET_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "bullet.hpp"

namespace sanguis
{
namespace draw
{

class rocket : public bullet {
public:
	rocket(
		draw::environment const &,
		entity_id id,
		sge::string const &name);
private:
	void on_decay();
};

}
}

#endif
