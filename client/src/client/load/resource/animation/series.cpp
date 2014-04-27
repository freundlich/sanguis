/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sanguis/client/load/resource/animation/entity.hpp>
#include <sanguis/client/load/resource/animation/entity_vector.hpp>
#include <sanguis/client/load/resource/animation/series.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::resource::animation::series::series()
:
	entities_()
{
}

sanguis::client::load::resource::animation::series::series(
	sanguis::client::load::resource::animation::entity_vector const &_entities
)
:
	entities_(
		_entities
	)
{
}

sanguis::client::load::resource::animation::series::series(
	sanguis::client::load::resource::animation::entity_vector &&_entities
)
:
	entities_(
		std::move(
			_entities
		)
	)
{
}

void
sanguis::client::load::resource::animation::series::push_back(
	sanguis::client::load::resource::animation::entity const &_entity
)
{
	entities_.push_back(
		_entity
	);
}

sanguis::client::load::resource::animation::entity_vector &
sanguis::client::load::resource::animation::series::entities()
{
	return entities_;
}

sanguis::client::load::resource::animation::entity_vector const &
sanguis::client::load::resource::animation::series::entities() const
{
	return entities_;
}

sanguis::client::load::resource::animation::series::const_iterator
sanguis::client::load::resource::animation::series::begin() const
{
	return entities_.begin();
}

sanguis::client::load::resource::animation::series::const_iterator
sanguis::client::load::resource::animation::series::end() const
{
	return entities_.end();
}

bool
sanguis::client::load::resource::animation::series::empty() const
{
	return entities_.empty();
}