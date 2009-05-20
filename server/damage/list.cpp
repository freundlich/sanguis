#include "list.hpp"
#include "meta.hpp"
#include <algorithm>

sanguis::server::damage::list::list(
	value_type const t)
{
	std::fill(
		array_.begin(),
		array_.end(),
		t
	);
}

sanguis::server::damage::list::list(
	meta const &m)
{
	std::fill(
		array_.begin(),
		array_.end(),
		static_cast<value_type>(0)
	);

	array_[m.type()] = m.value();
}

sanguis::server::damage::list &
sanguis::server::damage::list::operator()(
	meta const &m)
{
	array_[m.type()] = m.value();
	return *this;
}

sanguis::server::damage::list::
operator sanguis::server::damage::array() const
{
	return array_;
}
