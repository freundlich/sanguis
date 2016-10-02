#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_BUFFS_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_BUFFS_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/buff_type_vector_fwd.hpp>
#include <sanguis/messages/roles/buff_type_container.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

typedef
fcppt::record::element<
	sanguis::messages::roles::buff_type_container,
	sanguis::messages::adapted_types::buff_type_vector
>
add_with_buffs;

}
}
}
}

#endif
