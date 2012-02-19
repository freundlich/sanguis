#ifndef SANGUIS_MESSAGES_SERIALIZATION_READER_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READER_HPP_INCLUDED

#include <sanguis/messages/serialization/reader_fwd.hpp>
#include <sanguis/messages/serialization/istream.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

class reader
{
	FCPPT_NONASSIGNABLE(
		reader
	);
public:
	explicit reader(
		serialization::istream &
	);

	template<
		typename Msg
	>
	auto_ptr operator()() const;
private:
	serialization::istream &is_;
};

}
}
}

#endif