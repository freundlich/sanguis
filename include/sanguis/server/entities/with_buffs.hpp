#ifndef SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED

#include <sanguis/server/buffs/buff_fwd.hpp>
#include <sanguis/server/buffs/comparator.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_buffs_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <set>
#include <typeindex>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_buffs
:
	public virtual sanguis::server::entities::base
{
	FCPPT_NONCOPYABLE(
		with_buffs
	);
public:
	void
	add_buff(
		sanguis::server::buffs::unique_ptr &&
	);

	void
	remove_buff(
		sanguis::server::buffs::buff &
	);
protected:
	with_buffs();

	~with_buffs();

	void
	update()
	override;
private:
	typedef
	std::multiset<
		sanguis::server::buffs::unique_ptr,
		sanguis::server::buffs::comparator
	>
	buff_set;

	typedef
	std::unordered_map<
		std::type_index,
		buff_set
	>
	buff_map;

	buff_map buffs_;
};

}
}
}

#endif
