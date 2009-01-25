#include "add_pickup.hpp"
#include "instantiate_serialize.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::add_pickup, "add_pickup")

sanguis::messages::add_pickup::add_pickup()
{}

sanguis::messages::add_pickup::add_pickup(
	entity_id const id,
	pickup_type::type const ptype_,
	pos_type const &pos_,
	space_unit const angle_,
	space_unit const health_,
	space_unit const max_health_,
	dim_type const &dim_)
:
	add(
		id,
		entity_type::pickup,
		pos_,
		angle_,
		vector2::null(), // speed
		health_,
		max_health_,
		dim_),
	ptype_(ptype_)
{}

sanguis::pickup_type::type
sanguis::messages::add_pickup::ptype() const
{
	return ptype_;
}

template<typename Archive>
void sanguis::messages::add_pickup::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<add>(*this)
	   & ptype_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(add_pickup)
