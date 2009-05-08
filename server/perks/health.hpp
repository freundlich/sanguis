#ifndef SANGUIS_SERVER_PERKS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_HEALTH_HPP_INCLUDED

#include "perk.hpp"
#include "../space_unit.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

class health : public perk {
public:
	health();
private:
	void do_apply(
		entities::entity &,
		time_type,
		environment const &);
	bool can_raise_level() const;
};

}
}
}

#endif