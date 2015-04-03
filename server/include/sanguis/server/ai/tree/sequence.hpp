#ifndef SANGUIS_SERVER_AI_TREE_SEQUENCE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_SEQUENCE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/tree/basic_sequence.hpp>
#include <sanguis/server/ai/tree/container.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace tree
{

class sequence
:
	public sanguis::server::ai::tree::basic_sequence
{
	FCPPT_NONCOPYABLE(
		sequence
	);
public:
	explicit
	sequence(
		sanguis::server::ai::tree::container &&
	);

	~sequence()
	override;
private:
	sanguis::server::ai::status
	run(
		sanguis::duration
	)
	override;

	sanguis::server::ai::tree::container::iterator current_;
};

}
}
}
}

#endif