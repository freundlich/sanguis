set(
	SANGUIS_CORE_FILES
	include/sanguis/app_name.hpp
	include/sanguis/company_name.hpp
	include/sanguis/config_app_name.hpp
	include/sanguis/log_level_streams.hpp
	include/sanguis/log_location.hpp
	src/app_name.cpp
	src/company_name.cpp
	src/config_app_name.cpp
	src/log_level_streams.cpp
	src/log_location.cpp
)

sanguis_add_library(
	core
	"${SANGUIS_CORE_FILES}"
	DEPS
		${sgeconfig_TARGET}
		${fcppt_core_TARGET}
		${fcppt_log_TARGET}
)
