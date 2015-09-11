#ifndef SANGUIS_SERVER_DISPATCH_DEFAULT_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_DISPATCH_DEFAULT_FUNCTION_HPP_INCLUDED

#include <sanguis/messages/client/base_fwd.hpp>
#include <sanguis/server/player_id_fwd.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

typedef
fcppt::function<
	boost::statechart::result (
		sanguis::server::player_id,
		sanguis::messages::client::base const &
	)
>
dispatch_default_function;

}
}

#endif