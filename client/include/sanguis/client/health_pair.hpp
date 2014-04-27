#ifndef SANGUIS_CLIENT_HEALTH_PAIR_HPP_INCLUDED
#define SANGUIS_CLIENT_HEALTH_PAIR_HPP_INCLUDED

#include <sanguis/client/health.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/max_health.hpp>


namespace sanguis
{
namespace client
{

class health_pair
{
public:
	health_pair(
		sanguis::client::health,
		sanguis::client::max_health
	);

	sanguis::client::health const
	health() const;

	sanguis::client::max_health const
	max_health() const;
private:
	sanguis::client::health health_;

	sanguis::client::max_health max_health_;
};

}
}

#endif