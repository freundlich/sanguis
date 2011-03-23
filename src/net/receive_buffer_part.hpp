#ifndef SANGUIS_NET_RECEIVE_BUFFER_PART_HPP_INCLUDED
#define SANGUIS_NET_RECEIVE_BUFFER_PART_HPP_INCLUDED

#include "receive_buffer_part_fwd.hpp"
#include "size_type.hpp"
#include "value_type.hpp"
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace net
{

class receive_buffer_part
{
	FCPPT_NONASSIGNABLE(
		receive_buffer_part
	);
public:
	typedef net::value_type *pointer;

	typedef net::size_type size_type;

	receive_buffer_part(
		pointer begin,
		pointer end
	);

	pointer
	begin() const;

	pointer
	end() const;

	size_type
	size() const;

	bool
	empty() const;
private:
	pointer const
		begin_,
		end_;
};

}
}

#endif