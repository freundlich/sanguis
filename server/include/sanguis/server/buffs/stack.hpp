#ifndef SANGUIS_SERVER_BUFFS_STACK_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_STACK_HPP_INCLUDED

#include <sanguis/server/buffs/buff_fwd.hpp>
#include <sanguis/server/buffs/comparator.hpp>
#include <sanguis/server/buffs/stack_fwd.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

class stack
{
	FCPPT_NONCOPYABLE(
		stack
	);
public:
	stack();

	stack(
		stack &&
	);

	stack &
	operator=(
		stack &&
	);

	~stack();

	void
	insert(
		sanguis::server::buffs::unique_ptr &&
	);

	void
	erase(
		sanguis::server::buffs::buff const &
	);

	bool
	empty() const;

	sanguis::server::buffs::buff &
	highest_buff();

	sanguis::server::buffs::buff const &
	highest_buff() const;
private:
	typedef
	std::multiset<
		sanguis::server::buffs::unique_ptr,
		sanguis::server::buffs::comparator
	>
	set;

	set impl_;
};

}
}
}

#endif