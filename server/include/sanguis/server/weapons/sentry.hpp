#ifndef SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/server/entities/optional_base_ref_fwd.hpp>
#include <sanguis/server/weapons/attack_fwd.hpp>
#include <sanguis/server/weapons/sentry_parameters_fwd.hpp>
#include <sanguis/server/weapons/spawn.hpp>
#include <sanguis/server/weapons/spawn_weapon.hpp>
#include <sanguis/server/weapons/attributes/health.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class sentry
:
	public sanguis::server::weapons::spawn
{
	FCPPT_NONCOPYABLE(
		sentry
	);
public:
	sentry(
		sanguis::random_generator &,
		sanguis::server::weapons::spawn_weapon const &,
		sanguis::server::weapons::sentry_parameters const &
	);

	~sentry()
	override;
private:
	sanguis::server::entities::optional_base_ref const
	do_spawn(
		sanguis::server::weapons::attack const &,
		sanguis::server::weapons::spawn_weapon const &
	)
	override;

	sanguis::weapon_attribute_vector
	extra_attributes() const
	override;

	sanguis::server::weapons::attributes::health const health_;
};

}
}
}

#endif
