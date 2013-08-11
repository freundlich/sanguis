#ifndef SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class pistol
:
	public sanguis::server::weapons::weapon
{
	FCPPT_NONCOPYABLE(
		pistol
	);
public:
	pistol(
		sanguis::diff_clock const &,
		sanguis::weapon_type,
		sanguis::server::weapons::base_cooldown,
		sanguis::server::weapons::damage,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::magazine_size,
		sanguis::server::weapons::reload_time,
		sanguis::server::weapons::range
	);

	~pistol();
private:
	void
	do_attack(
		sanguis::server::weapons::delayed_attack const &
	);

	sanguis::string_vector
	attributes() const
	override;

	sanguis::server::weapons::damage const damage_;
};

}
}
}

#endif
