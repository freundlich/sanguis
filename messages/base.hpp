#ifndef SANGUIS_MESSAGES_BASE_HPP_INCLUDED
#define SANGUIS_MESSAGES_BASE_HPP_INCLUDED

#include "base_fwd.hpp"
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace messages
{

class base {
	SGE_NONCOPYABLE(base)
protected:
	base();
public:
	virtual ~base();

	virtual majutsu::const_raw_pointer
	data() const = 0;

	virtual majutsu::size_type
	size() const = 0;
};

}
}

#endif
