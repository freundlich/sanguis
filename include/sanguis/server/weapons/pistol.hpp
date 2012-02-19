#ifndef SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED

#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

class pistol
:
	public weapon
{
	FCPPT_NONCOPYABLE(
		pistol
	);
public:
	pistol(
		sanguis::diff_clock const &,
		weapon_type::type,
		weapons::base_cooldown,
		weapons::damage,
		weapons::cast_point,
		weapons::magazine_size,
		weapons::reload_time,
		weapons::range
	);

	~pistol();
private:
	void
	do_attack(
		delayed_attack const &
	);

	weapons::damage const damage_;
};

}
}
}

#endif