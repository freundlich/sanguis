#include "time_to_gregorian.hpp"
#include <boost/date_time/date_defs.hpp>
#include <ctime>

boost::gregorian::date const
sanguis::client::draw2d::sunlight::time_to_gregorian(
	std::tm const &tm_
)
{
	return
		boost::gregorian::date(
			static_cast<
				unsigned short
			>(
				tm_.tm_year + 1900 // year starts at 1900
			),
			static_cast<
				unsigned short
			>(
				tm_.tm_mon + 1 // boost::date_time::Jan is 1
			),
			static_cast<
				unsigned short
			>(
				tm_.tm_mday
			)
		);
}
