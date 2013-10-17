#include <sanguis/messages/add_friend.hpp>
#include <sanguis/messages/instantiate_message.hpp>
#include <alda/serialization/load/dynamic_len.hpp>
#include <alda/serialization/load/optional.hpp>
#include <alda/serialization/load/static_size.hpp>


SANGUIS_MESSAGES_INSTANTIATE_MESSAGE(
	sanguis::messages::add_friend
);
