#ifndef SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED

#include "influence.hpp"
#include "../entities/entity_fwd.hpp"
#include "../collision/base.hpp"
#include "../teams.hpp"
#include "../types.hpp"

namespace sanguis
{
namespace server
{

struct environment;

namespace auras
{

class aura : public collision::base {
public:
	virtual ~aura();

	void pos(
		pos_type const &);
protected:
	aura(
		environment const &,
		circle_type const &,
		team::type team,
		influence::type);
private:
	bool
	can_collide_with(
		collision::base const &) const;

	void
	collision(
		collision::base &);

	virtual void
	do_effect(
		entities::entity &) = 0;

	team::type const      team_;
	influence::type const influence_;
};

}
}
}

#endif
