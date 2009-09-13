#include "random.hpp"
#include "object.hpp"
#include <sge/make_auto_ptr.hpp>

sanguis::server::world::object_auto_ptr
sanguis::server::world::random(
	context_ptr const ctx_,
	sge::collision::system_ptr const collision_system_
)
{
	// TODO:
	return sge::make_auto_ptr<
		object
	>(
		ctx_,
		collision_system_
	);
}
