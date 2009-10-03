#include "with_perks.hpp"
#include "../perks/perk.hpp"
#include "../log.hpp"
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>

void
sanguis::server::entities::with_perks::add_perk(
	perks::auto_ptr p
)
{
	perk_type::type const type_(
		p->type()
	);

	perk_container::iterator it(
		perks_.find(
			type_
		)
	);

	if(it != perks_.end())
	{
		perks::perk &perk_(
			*it->second
		);

		if(perk_.can_raise_level())
			perk_.raise_level();
		else
		{
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< SGE_TEXT("Tried to raise perk level of a perk which can't do this.")
			);
		}
		return;
	}

	p->apply(
		*this
	);

	perks_.insert(
		type_,
		p
	);
}

sanguis::server::entities::with_perks::with_perks()
:
	base(),
	perks_()
{}

sanguis::server::entities::with_perks::~with_perks()
{}

void
sanguis::server::entities::with_perks::on_update(
	time_type const time
)
{
	BOOST_FOREACH(
		perk_container::reference p,
		perks_
	)
		p.second->update(
			*this,
			time,
			environment()
		);
}

bool
sanguis::server::entities::with_perks::perk_choosable(
	perk_type::type const pt
) const
{
	perk_container::const_iterator const it(
		perks_.find(
			pt
		)
	);

	return it == perks_.end()
		|| it->second->can_raise_level();
}