#ifndef SANGUIS_SERVER_AURAS_BUFF_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_BUFF_HPP_INCLUDED

#include <sanguis/aura_type.hpp>
#include <sanguis/optional_aura_type_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/influence_fwd.hpp>
#include <sanguis/server/buffs/create_callback.hpp>
#include <sanguis/server/buffs/provider.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

class buff
:
	public sanguis::server::auras::aura
{
	FCPPT_NONCOPYABLE(
		buff
	);
public:
	buff(
		sanguis::server::radius,
		sanguis::server::team,
		sanguis::aura_type,
		sanguis::server::auras::influence,
		sanguis::server::buffs::create_callback const &
	);

	~buff();
private:
	sanguis::optional_aura_type const
	type() const
	override;

	void
	enter(
		sanguis::server::entities::with_body &
	);

	void
	leave(
		sanguis::server::entities::with_body &
	);

	sanguis::aura_type const aura_type_;

	sanguis::server::buffs::create_callback const create_callback_;

	sanguis::server::buffs::provider provider_;
};

}
}
}

#endif