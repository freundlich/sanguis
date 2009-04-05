#ifndef SANGUIS_MESSAGES_CONCRETE_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONCRETE_IMPL_HPP_INCLUDED

#include "concrete.hpp"

template<
	typename T
>
sanguis::messages::concrete<T>::concrete(
	T const &value_)
:
	value_(value_)
{}
	
template<
	typename T
>
T const &
sanguis::messages::concrete<T>::value() const
{
	return value_;
}

template<
	typename T
>
majutsu::const_raw_pointer
sanguis::messages::concrete<T>::data() const
{
	return value_.memory().data();
}

template<
	typename T
>
majutsu::size_type
sanguis::messages::concrete<T>::size() const
{
	return value_.memory().size();
}

#endif
