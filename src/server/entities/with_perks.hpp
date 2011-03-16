#ifndef SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED

#include "base.hpp"
#include "../perks/perk_fwd.hpp"
#include "../perks/unique_ptr.hpp"
#include "../../perk_type.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_perks
:
	public virtual base
{
	FCPPT_NONCOPYABLE(
		with_perks
	);
public:
	void
	add_perk(
		perks::unique_ptr
	);
protected:
	with_perks();

	~with_perks();

	void
	on_update(
		time_type
	);

	virtual bool
	perk_choosable(
		perk_type::type
	) const;
private:
	typedef boost::ptr_map<
		perk_type::type,
		perks::perk
	> perk_container;

	perk_container perks_;
};

}
}
}

#endif
