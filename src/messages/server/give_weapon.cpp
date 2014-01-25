#include <sanguis/messages/server/give_weapon.hpp>
#include <sanguis/messages/server/instantiate_message.hpp>
#include <alda/serialization/load/dynamic_len.hpp>
#include <alda/serialization/load/optional.hpp>
#include <alda/serialization/load/static_size.hpp>
#include <alda/serialization/load/variant.hpp>


SANGUIS_MESSAGES_SERVER_INSTANTIATE_MESSAGE(
	sanguis::messages::server::give_weapon
);