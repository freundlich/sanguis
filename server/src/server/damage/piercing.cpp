#include <sanguis/server/damage/piercing.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/wrapper.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sanguis::server::damage::wrapper const // NOLINT(fuchsia-statically-constructed-objects)
sanguis::server::damage::piercing( // NOLINT(cert-err58-cpp)
	sanguis::server::damage::type::piercing
);

FCPPT_PP_POP_WARNING
