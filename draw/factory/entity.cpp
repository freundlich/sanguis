#include "entity.hpp"
#include "../bullet.hpp"
#include "../player.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::entity(
	entity_id const id,
	system &sys,
	entity_type::type const type)
{
	// TODO: make this prettier and generate code for it using a template
	switch(type) {
	case entity_type::player:
		return entity_ptr(
			new player(
				id,
				sys));
	case entity_type::bullet:
		return entity_ptr(
			new bullet(
				id,
				sys));
	case entity_type::enemy:
		throw sge::exception(
			SGE_TEXT("entity_type::enemy cannot be created using entity!"));
	default:
		throw sge::exception(
			SGE_TEXT("draw::factory::entity: missing loading code!"));
	}
}
