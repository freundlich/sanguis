#include <sanguis/buff_type.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/stack.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/get_or_insert_result.hpp>
#include <fcppt/container/get_or_insert_with_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <typeindex>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::entities::with_buffs::add_buff(
	sanguis::server::buffs::unique_ptr &&_buff
)
{
	using
	result_type
	=
	fcppt::container::get_or_insert_result<
		sanguis::server::buffs::stack &
	>;

	sanguis::server::buffs::buff const &cur_buff(
		*_buff
	);

	result_type const result(
		fcppt::container::get_or_insert_with_result(
			buffs_,
			std::type_index{
				typeid(
					cur_buff
				)
			},
			[](
				std::type_index
			)
			{
				return
					sanguis::server::buffs::stack();
			}
		)
	);

	sanguis::server::buffs::stack &set(
		result.element()
	);

	if(
		!result.inserted()
	)
	{
		set.highest_buff().remove();
	}

	set.insert(
		std::move(
			_buff
		)
	);

	set.highest_buff().add();

	if(
		result.inserted()
	)
	{
		FCPPT_ASSERT_OPTIONAL_ERROR(
			this->environment()
		).get().add_buff(
			this->id(),
			cur_buff.type()
		);
	}
}

void
sanguis::server::entities::with_buffs::remove_buff(
	sanguis::server::buffs::buff &_buff
)
{
	sanguis::buff_type const buff_type(
		_buff.type()
	);

	std::type_index const index(
		typeid(
			_buff
		)
	);

	buff_map::iterator const it(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::container::find_opt_iterator(
				buffs_,
				index
			)
		)
	);

	sanguis::server::buffs::stack &set(
		it->second
	);

	set.highest_buff().remove();

	set.erase(
		_buff
	);

	if(
		set.empty()
	)
	{
		FCPPT_ASSERT_OPTIONAL_ERROR(
			this->environment()
		).get().remove_buff(
			this->id(),
			buff_type
		);

		buffs_.erase(
			it
		);
	}
	else
	{
		set.highest_buff().add();
	}
}

sanguis::server::entities::with_buffs::with_buffs()
:
	buffs_()
{
}

sanguis::server::entities::with_buffs::~with_buffs()
= default;

sanguis::buff_type_vector
sanguis::server::entities::with_buffs::buff_types() const
{
	return
		fcppt::algorithm::map<
			sanguis::buff_type_vector
		>(
			buffs_,
			[](
				buff_map::value_type const &_buffs
			)
			{
				return
					_buffs.second.highest_buff().type();
			}
		);
}

void
sanguis::server::entities::with_buffs::update()
{
	for(
		buff_map::value_type &elem
		:
		buffs_
	)
	{
		elem.second.highest_buff().update();
	}
}
