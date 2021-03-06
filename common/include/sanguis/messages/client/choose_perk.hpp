#ifndef SANGUIS_MESSAGES_CLIENT_CHOOSE_PERK_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CHOOSE_PERK_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/messages/adapted_types/enum.hpp>
#include <sanguis/messages/client/choose_perk_fwd.hpp>
#include <sanguis/messages/client/declare_message.hpp>
#include <alda/message/object.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SANGUIS_MESSAGES_CLIENT_DECLARE_MESSAGE(
	sanguis::messages::client::choose_perk
);

FCPPT_PP_POP_WARNING

#endif
