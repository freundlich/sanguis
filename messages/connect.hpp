#ifndef SANGUIS_MESSAGES_CONNECT_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONNECT_HPP_INCLUDED

#include "base.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class connect : public base {
public:
	connect();
private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
