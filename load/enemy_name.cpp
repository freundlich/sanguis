#include "enemy_name.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::string const
sanguis::load::enemy_name(
	enemy_type::type const etype)
{
	switch(etype) {
	case enemy_type::wolf_black:
		return SGE_TEXT("wolf_black");
	case enemy_type::wolf_brown:
		return SGE_TEXT("wolf_brown");
	case enemy_type::wolf_white:
		return SGE_TEXT("wolf_white");
	case enemy_type::zombie00:
		return SGE_TEXT("zombie00");
	case enemy_type::zombie01:
		return SGE_TEXT("zombie01");
	default:
		throw sge::exception(
			SGE_TEXT("load::enemy_name: missing loading code!"));
	}
}