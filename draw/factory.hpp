#ifndef SANGUIS_DRAW_FACTORY_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_HPP_INCLUDED

#include "entity.hpp"
#include "../messages/fwd.hpp"
#include <sge/renderer/types.hpp>
#include <memory>

namespace sanguis
{
namespace draw
{
namespace factory
{

typedef std::auto_ptr<entity> entity_ptr;
entity_ptr create_entity(
	const messages::add&,
	const sge::screen_size_t &);

}
}
}

#endif
