#ifndef SANGUIS_SERVER_LOAD_HPP_INCLUDED
#define SANGUIS_SERVER_LOAD_HPP_INCLUDED

#include <sanguis/load/model/path.hpp>
#include <sanguis/server/load_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

class load
{
	FCPPT_NONMOVABLE(
		load
	);
public:
	load();

	~load();

	[[nodiscard]]
	sanguis::server::radius
	model_dim(
		sanguis::load::model::path const &
	) const;
private:
	using
	dim_map
	=
	std::map<
		sanguis::load::model::path,
		sanguis::server::radius
	>;

	mutable dim_map dims_;
};

}
}

#endif
