#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_PARAMETERS_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_PARAMETERS_IMPL_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/client/draw2d/entities/with_auras_parameters_decl.hpp>
#include <sanguis/load/auras/context_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>


template<
	typename Base
>
sanguis::client::draw2d::entities::with_auras_parameters<
	Base
>::with_auras_parameters(
	sanguis::diff_clock const &_diff_clock,
	sanguis::load::auras::context &_aura_load_context,
	sanguis::client::draw2d::sprite::normal::system &_normal_system,
	sanguis::aura_type_vector const &_auras,
	Base const &_base
)
:
	diff_clock_(
		_diff_clock
	),
	aura_load_context_(
		_aura_load_context
	),
	normal_system_(
		_normal_system
	),
	auras_(
		_auras
	),
	base_(
		_base
	)
{
}

template<
	typename Base
>
sanguis::diff_clock const &
sanguis::client::draw2d::entities::with_auras_parameters<
	Base
>::diff_clock() const
{
	return
		diff_clock_;
}

template<
	typename Base
>
sanguis::load::auras::context &
sanguis::client::draw2d::entities::with_auras_parameters<
	Base
>::aura_load_context() const
{
	return
		aura_load_context_;
}

template<
	typename Base
>
sanguis::client::draw2d::sprite::normal::system &
sanguis::client::draw2d::entities::with_auras_parameters<
	Base
>::normal_system() const
{
	return
		normal_system_;
}

template<
	typename Base
>
sanguis::aura_type_vector const &
sanguis::client::draw2d::entities::with_auras_parameters<
	Base
>::auras() const
{
	return
		auras_;
}

template<
	typename Base
>
Base const &
sanguis::client::draw2d::entities::with_auras_parameters<
	Base
>::base() const
{
	return
		base_;
}

#endif