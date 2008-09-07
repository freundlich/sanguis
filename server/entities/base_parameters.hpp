#ifndef SANGUIS_SERVER_ENTITIES_BASE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BASE_PARAMETERS_HPP_INCLUDED

#include "property_map.hpp"
#include "../environment.hpp"
#include "../teams.hpp"
#include "../types.hpp"
#include "../../damage_type.hpp"
#include "../../entity_type.hpp"
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace server
{

struct environment;

namespace entities
{

class base_parameters : boost::noncopyable {
public:
	base_parameters(
		environment const &,
		armor_array const &,
		pos_type const &pos,
		space_unit angle,
		space_unit direction,
		team::type team_,
		property_map const &properties,
		entity_type::type type_,
		bool invulnerable,
		dim_type const &collision_dim);
	
	environment const &env() const;
	armor_array const &armor() const;
	pos_type const &pos() const;
	space_unit angle() const;
	space_unit direction() const;
	team::type team() const;
	property_map const &properties() const;
	entity_type::type type() const;
	bool invulnerable() const;
	dim_type const &collision_dim() const;
private:
	environment const          &env_;
	armor_array const          &armor_;
	pos_type const   pos_;
	space_unit const angle_,
	                           direction_;
	team::type const           team_;
	property_map const         &properties_;
	entity_type::type const    type_;
	bool const                 invulnerable_;
	dim_type const   collision_dim_;
};

}
}
}

#endif