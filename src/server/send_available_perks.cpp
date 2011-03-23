#include "send_available_perks.hpp"
#include "perks/list.hpp"
#include "entities/player.hpp"
#include "../messages/available_perks.hpp"
#include "../messages/create.hpp"
#include <fcppt/container/raw_vector_impl.hpp>

void
sanguis::server::send_available_perks(
	entities::player const &p,
	unicast_callback const &send
)
{
	perks::list const &list(
		p.available_perks()
	);

	send(
		p.player_id(),
		messages::create(
			messages::available_perks(
				p.id(),
				messages::types::enum_vector(
					list.begin(),
					list.end()
				)
			)
		)
	);
}