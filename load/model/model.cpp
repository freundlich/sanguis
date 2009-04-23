#include "model.hpp"
#include "split_first_slash.hpp"
#include "get_entry.hpp"
#include "optional_delay.hpp"
#include "../../exception.hpp"
#include "../resource/context.hpp"
#include "../resource/textures.hpp"
#include "../log.hpp"
#include <sge/filesystem/directory_iterator.hpp>
#include <sge/filesystem/is_directory.hpp>
#include <sge/filesystem/stem.hpp>
#include <sge/filesystem/extension.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/log/headers.hpp>
#include <sge/parse/json/parse_file.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/member_name_equal.hpp>
#include <sge/fstream.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <utility>
#include <functional>
#include <algorithm>
#include <string>

// TODO: split this stuff!

namespace
{

sge::string const header_name(
	SGE_TEXT("header")
);

sge::renderer::dim_type const
load_dim(
	sge::parse::ini::entry_vector const &entries)
{
	return sge::renderer::dim_type(
		static_cast<sge::renderer::size_type>(
			sanguis::load::model::get_entry<int>(
				entries,
				SGE_TEXT("cell_width")
			)
		),
		static_cast<sge::renderer::size_type>(
			sanguis::load::model::get_entry<int>(
				entries,
				SGE_TEXT("cell_height")
			)
		)
	);
}

sanguis::load::model::optional_delay const
load_delay(
	sge::parse::ini::entry_vector const &entries)
{
	try
	{
		return sanguis::load::model::get_entry<int>(
			entries,
			SGE_TEXT("delay")
		);
	}
	catch(sanguis::exception const &e)
	{
		return sanguis::load::model::optional_delay();
	}
}

}

sanguis::load::model::model::model(
	sge::filesystem::path const &path,
	resource::context const &ctx)
:
	path(path),
	parts()
{
	sge::filesystem::path const file(
		path / SGE_TEXT("config.json")
	);

	sge::parse::json::object global_entries;
	
	if(
		!sge::parse::json::parse_file(
			path,
			global_entries
		)
	)
	{
		SGE_LOG_WARNING(
			sanguis::load::log(),
			sge::log::_1
				<< global_ini
				<< SGE_TEXT(" contains errors!")
			);
	}

	sge::parse::json::member_vector::const_iterator const header_it(
		std::find_if(
			global_entries.begin(),
			global_entries.end(),
			sge::parse::json::member_name_equal(
				header_name
			)
		)
	);

	if(header_it == global_entries.end())
		throw sanguis::exception(
			SGE_TEXT("header subsection not found in ")
			+ file.string()
		);

	sge::parse::json::object const header(
		boost::get<
			sge::parse::json::object
		>(
			header_it->value_
		)
	);

	sge::renderer::dim_type const cell_size(
		load_dim(
			header.members
		)
	);

	optional_delay const opt_delay(
		load_delay(
			header.members
		)
	);

	BOOST_FOREACH(
		sge::parse::json::member_vector::const_reference r,
		global_entries
	)
	{
		if(r.name == header_name)
			continue;

		sge::texture::part_ptr const tex(
			ctx.textures().load(
				file
			)
		);


		BOOST_FOREACH(
			sge::parse::ini::section_vector::const_reference section,
			sections
		)
		{	
			split_pair const names(
				split_first_slash(
					section.header
				)
			);

			part_map::iterator it(
				parts.find(
					names.first
				)
			);

			SGE_LOG_DEBUG(
				log(),
				sge::log::_1
					<< SGE_TEXT("Adding category ")
					<< names.first
					<< SGE_TEXT(" in ")
					<< path
					<< SGE_TEXT(". Rest: ")
					<< names.second
			);

			if(it == parts.end())
			{
				std::pair<part_map::iterator, bool> const ret(
					parts.insert(
						std::make_pair(
							names.first,
							part(
								global_parameters(
									cell_size,
									opt_delay
								)
							)
						)
					)
				);
				
				it = ret.first;
			}

			it->second.add(
				section.entries,
				names.second,
				tex
			);
		}
	}
}

sanguis::load::model::part const &
sanguis::load::model::model::operator[](
	sge::string const &name) const
{
	part_map::const_iterator const it(
		parts.find(
			name
		)
	);

	if(it == parts.end())
		throw exception(
			SGE_TEXT("Category \"")
			+ name
			+ SGE_TEXT("\" not found in ")
			+ path.string()
		);
	
	return it->second;
}

sanguis::load::model::model::const_iterator
sanguis::load::model::model::begin() const
{
	return parts.begin();
}

sanguis::load::model::model::const_iterator
sanguis::load::model::model::end() const
{
	return parts.end();
} 
sanguis::load::model::model::size_type
sanguis::load::model::model::size() const
{
	return parts.size();
}
