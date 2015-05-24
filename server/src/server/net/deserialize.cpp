#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/optional_unique_ptr.hpp>
#include <sanguis/messages/client/serialization/deserialize.hpp>
#include <sanguis/net/deserialize.hpp>
#include <sanguis/server/net/deserialize.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>


sanguis::messages::client::optional_unique_ptr
sanguis::server::net::deserialize(
	alda::net::buffer::circular_receive::object &_buffer
)
{
	return
		sanguis::net::deserialize(
			_buffer,
			&sanguis::messages::client::serialization::deserialize
		);
}
