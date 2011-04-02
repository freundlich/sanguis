#ifndef SANGUIS_SERVER_PERKS_IAS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_IAS_HPP_INCLUDED

#include "perk.hpp"
#include "level_diff.hpp"
#include "../level.hpp"
#include "../entities/base_fwd.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

class ias
:
	public perk
{
	FCPPT_NONCOPYABLE(
		ias
	);
public:
	ias();

	~ias();
private:
	void
	change(
		entities::base &,
		level_diff
	);

	server::level const
	max_level() const;
};

}
}
}

#endif
