#include "bullet.hpp"
#include "factory.hpp"
#include "player.hpp"
#include "resource_factory.hpp"
#include "coord_transform.hpp"
#include "z_ordering.hpp"
#include "../messages/add.hpp"
#include "../entity_type.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::create_entity(
	const messages::add& m,
	const sge::screen_size_t &screen_size)
{
	// TODO: make this prettier and generate code for it using a template
	switch(m.type()) {
	case entity_type::player:
		return entity_ptr(
			new player(
				m.id(),
				virtual_to_screen(screen_size, m.pos()),
				static_cast<sge::space_unit>(m.angle()),
				// double conversion here (deliberately)
				sge::math::structure_cast<sge::space_unit>(
					virtual_to_screen(
						screen_size,
						m.speed()))
				));
	case entity_type::bullet:
		return entity_ptr(
			new bullet(
				m.id(),
				virtual_to_screen(screen_size, m.pos()),
				static_cast<sge::space_unit>(m.angle()),
				sge::math::structure_cast<sge::space_unit>(
					virtual_to_screen(
						screen_size,
						m.speed()))));
	default:
		throw sge::exception(SGE_TEXT("draw::factory: missing loading code!"));
	}
}
