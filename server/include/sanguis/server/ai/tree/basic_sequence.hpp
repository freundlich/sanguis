#ifndef SANGUIS_SERVER_AI_TREE_BASIC_SEQUENCE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_BASIC_SEQUENCE_HPP_INCLUDED

#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/ai/tree/container.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace tree
{

class basic_sequence
:
	public sanguis::server::ai::tree::base
{
	FCPPT_NONCOPYABLE(
		basic_sequence
	);
public:
	explicit
	basic_sequence(
		sanguis::server::ai::tree::container &&
	);

	~basic_sequence()
	override;
protected:
	sanguis::server::entities::transfer_result
	transfer()
	override;

	sanguis::server::ai::tree::container &
	get();
private:
	sanguis::server::ai::tree::container children_;
};

}
}
}
}

#endif
