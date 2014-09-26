#include <sanguis/server/entities/enemies/modifiers/amount.hpp>
#include <sanguis/server/entities/enemies/modifiers/create_callbacks.hpp>
#include <sanguis/server/random/amount.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>


sanguis::server::random::amount const
sanguis::server::entities::enemies::modifiers::amount()
{
	return
		fcppt::strong_typedef_construct_cast<
			sanguis::server::random::amount
		>(
			sanguis::server::entities::enemies::modifiers::create_callbacks().size()
		);
}
