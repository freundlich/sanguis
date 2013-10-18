#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_IMPL_HPP_INCLUDED

#include <sanguis/aura_type.hpp>
#include <sanguis/aura_type_vector.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/with_auras_decl.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_auras.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/parameters.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/load/auras/context.hpp>
#include <sge/sprite/center.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/timer/elapsed_fractional.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Base
>
sanguis::client::draw2d::entities::with_auras<
	Base
>::with_auras(
	sanguis::diff_clock const &_diff_clock,
	sanguis::load::auras::context &_aura_load_context,
	sanguis::client::draw2d::sprite::normal::system &_normal_system,
	sanguis::aura_type_vector const &_auras,
	parameters const &_parameters
)
:
	sanguis::client::draw2d::entities::ifaces::with_auras(),
	Base(
		_parameters
	),
	aura_load_context_(
		_aura_load_context
	),
	normal_system_(
		_normal_system
	),
	rotate_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			sanguis::duration_second(
				2
			)
		)
	),
	sprites_()
{
	for(
		auto const &aura
		:
		_auras
	)
		this->add_aura(
			aura
		);
}

template<
	typename Base
>
sanguis::client::draw2d::entities::with_auras<
	Base
>::~with_auras()
{
}

template<
	typename Base
>
void
sanguis::client::draw2d::entities::with_auras<
	Base
>::update()
{
	Base::update();

	for(
		auto &sprite
		:
		sprites_
	)
	{
		sge::sprite::center(
			sprite.second,
			this->center().get()
		);

		sprite.second.rotation(
			sge::timer::elapsed_fractional<
				sanguis::client::draw2d::sprite::rotation
			>(
				rotate_timer_
			)
			*
			fcppt::math::twopi<
				sanguis::client::draw2d::sprite::rotation
			>()
		);
	}

	sge::timer::reset_when_expired(
		rotate_timer_
	);
}

template<
	typename Base
>

void
sanguis::client::draw2d::entities::with_auras<
	Base
>::on_die()
{
	Base::on_die();

	sprites_.clear();
}

template<
	typename Base
>
void
sanguis::client::draw2d::entities::with_auras<
	Base
>::add_aura(
	sanguis::aura_type const _aura
)
{
	// Multiple inserts are ok
	sprites_.insert(
		std::make_pair(
			_aura,
			sanguis::client::draw2d::sprite::normal::object(
				sanguis::client::draw2d::sprite::normal::parameters()
				.connection(
					normal_system_.connection(
						sanguis::client::draw2d::z_ordering::aura
					)
				)
				.center(
					this->center().get()
				)
				.rotation(
					fcppt::literal<
						sanguis::client::draw2d::sprite::rotation
					>(
						0
					)
				)
				.texture(
					aura_load_context_.texture(
						_aura
					)
				)
				.texture_size()
			)
		)
	);
}

#endif
