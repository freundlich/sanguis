#ifndef SANGUIS_SERVER_WAVES_DEBUG_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_DEBUG_HPP_INCLUDED

#include "wave.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../../time_type.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

class debug
:
	public wave
{
	FCPPT_NONCOPYABLE(
		debug
	);
public:
	debug();

	~debug();
private:
	void
	process(
		time_type diff,
		environment::object &,
		environment::load_context &
	);

	bool
	ended() const;

	bool spawned_;
};

}
}
}

#endif
