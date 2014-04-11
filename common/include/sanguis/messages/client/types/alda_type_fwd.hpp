#ifndef SANGUIS_MESSAGES_CLIENT_TYPES_ALDA_TYPE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_TYPES_ALDA_TYPE_FWD_HPP_INCLUDED

#include <sanguis/messages/client/types/message.hpp>
#include <alda/type_enum_fcppt_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{
namespace types
{

typedef
alda::type_enum_fcppt<
	sanguis::messages::client::types::message
>
alda_type;

}
}
}
}

#endif