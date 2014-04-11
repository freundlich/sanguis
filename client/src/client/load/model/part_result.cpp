#include <sanguis/client/load/model/part.hpp>
#include <sanguis/client/load/model/part_map.hpp>
#include <sanguis/client/load/model/part_result.hpp>
#include <sanguis/model/cell_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::model::part_result::part_result(
	sanguis::model::cell_size const &_cell_size,
	sanguis::client::load::model::part_map &&_parts
)
:
	cell_size_(
		_cell_size
	),
	parts_(
		std::move(
			_parts
		)
	)
{
}

sanguis::client::load::model::part_result::part_result(
	part_result &&
) = default;

sanguis::client::load::model::part_result::~part_result()
{
}

sanguis::model::cell_size const &
sanguis::client::load::model::part_result::cell_size() const
{
	return
		cell_size_;
}

sanguis::client::load::model::part_map const &
sanguis::client::load::model::part_result::parts() const
{
	return
		parts_;
}