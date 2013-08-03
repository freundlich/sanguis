#ifndef SANGUIS_MESSAGES_PAUSE_HPP_INCLUDED
#define SANGUIS_MESSAGES_PAUSE_HPP_INCLUDED

#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/make_message_id.hpp>
#include <sanguis/messages/types/message.hpp>
#include <majutsu/composite.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	majutsu::composite<
		boost::mpl::vector1<
			sanguis::messages::make_message_id<
				sanguis::messages::types::message::pause
			>
		>
	>
>
pause;

}
}

#endif
