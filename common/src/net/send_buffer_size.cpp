#include <sanguis/net/send_buffer_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>


alda::net::buffer::max_send_size
sanguis::net::send_buffer_size()
{
	return
		alda::net::buffer::max_send_size(
			1024U * 64U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		);
}
