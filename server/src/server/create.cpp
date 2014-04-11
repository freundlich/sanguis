#include <sanguis/server/create.hpp>
#include <sanguis/server/object_base_unique_ptr.hpp>
#include <sanguis/server/object.hpp>
#include <alda/net/port.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::object_base_unique_ptr
sanguis::server::create(
	alda::net::port const _port
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::object
		>(
			_port
		);
}