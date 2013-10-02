#ifndef SANGUIS_SERVER_AI_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BASE_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/ai/base_fwd.hpp>
#include <sanguis/server/ai/sight_range_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base() = 0;

	virtual
	void
	in_range(
		sanguis::server::entities::with_body &
	);

	virtual
	void
	distance_changes(
		sanguis::server::entities::with_body &
	);

	virtual
	void
	out_of_range(
		sanguis::server::entities::with_body &
	);

	virtual
	void
	update(
		sanguis::creator::grid const &
	) = 0;

	// This could dynamically change in the future!
	virtual
	sanguis::server::ai::sight_range const
	sight_range() const = 0;
};

}
}
}

#endif
