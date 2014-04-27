#ifndef SANGUIS_SERVER_ENTITIES_CENTER_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_CENTER_SIMPLE_HPP_INCLUDED

#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class center_simple
:
	public virtual sanguis::server::entities::base
{
	FCPPT_NONCOPYABLE(
		center_simple
	);
protected:
	center_simple();
public:
	sanguis::server::center const
	center() const
	override
	final;

	virtual
	~center_simple() = 0;
protected:
	bool
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;
private:
	typedef fcppt::optional<
		sanguis::server::center
	> optional_center;

	optional_center center_;
};

}
}
}

#endif