#ifndef SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED

#include <sanguis/load/model/part_fwd.hpp>
#include <sanguis/load/model/weapon_category_fwd.hpp>
#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sanguis/load/resource/context_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class part
{
	FCPPT_NONCOPYABLE(
		part
	);
public:
	weapon_category const &
	operator[](
		weapon_type::type
	) const;

	~part();

	part(
		sge::parse::json::object const &,
		global_parameters const &
	);
private:
	typedef boost::ptr_map<
		weapon_type::type,
		weapon_category
	> category_map;

	category_map categories_;
};

}
}
}

#endif