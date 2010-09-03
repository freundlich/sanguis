#include "object.hpp"
#include "find_texture.hpp"
#include "global_parameters.hpp"
#include "json_header.hpp"
#include "load_delay.hpp"
#include "load_dim.hpp"
#include "optional_delay.hpp"
#include "parse_json.hpp"
#include "split_first_slash.hpp"
#include "part.hpp"
#include "../../exception.hpp"
#include "../resource/context.hpp"
#include "../resource/textures.hpp"
#include "../log.hpp"
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <fcppt/filesystem/is_directory.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/random/make_last_exclusive_range.hpp>
#include <fcppt/auto_ptr.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/text.hpp>
#include <boost/next_prior.hpp>
#include <boost/foreach.hpp>
#include <utility>

sanguis::load::model::object::~object()
{}

sanguis::load::model::part const &
sanguis::load::model::object::operator[](
	fcppt::string const &name
) const
{
	part_map::const_iterator const it(
		parts.find(
			name
		)
	);

	if(it == parts.end())
		throw exception(
			FCPPT_TEXT("Category \"")
			+ name
			+ FCPPT_TEXT("\" not found in ")
			+ path.string()
		);
	
	return *it->second;
}

sanguis::load::model::part const &
sanguis::load::model::object::random_part() const
{
	if(!random_part_)
		random_part_.reset(
			new part_rand(
				fcppt::random::make_last_exclusive_range(
					static_cast<part_map::size_type>(0),
					parts.size()
				)
			)
		);

	return
		*boost::next(
			parts.begin(),
			(*random_part_)()
		)->second;
}

sanguis::load::model::object::size_type
sanguis::load::model::object::size() const
{
	return parts.size();
}

sanguis::load::model::object::const_iterator
sanguis::load::model::object::begin() const
{
	return parts.begin();
}

sanguis::load::model::object::const_iterator
sanguis::load::model::object::end() const
{
	return parts.end();
}

sge::renderer::dim_type const
sanguis::load::model::object::dim() const
{
	return cell_size;
}

sanguis::load::model::object::object(
	fcppt::filesystem::path const &path,
	resource::context const &ctx
)
:
	path(path),
	parts()
{
	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Entering ")
			<< path.string()
	);

	try
	{
		construct(
			ctx
		);
	}
	catch(sge::exception const &e)
	{
		FCPPT_LOG_ERROR(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("model \"")
				<< path.string()
				<< FCPPT_TEXT("\": \"")
				<< e.string()
				<< FCPPT_TEXT('"')
		);

		throw;
	}
}

void
sanguis::load::model::object::construct(
	resource::context const &ctx
)
{
	sge::parse::json::object object_return;
	
	parse_json(
		path,
		object_return
	);

	sge::parse::json::member_vector const &global_entries(
		object_return.members
	);

	sge::parse::json::object const &header(
		json_header(
			global_entries
		)
	);

	cell_size = load_dim(
		header.members
	);

	optional_delay const opt_delay(
		load_delay(
			header.members
		)
	);

	optional_texture_identifier const texture(
		find_texture(
			global_entries
		)
	);

	BOOST_FOREACH(
		sge::parse::json::element_vector::const_reference r,
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			global_entries,
			FCPPT_TEXT("parts")
		).elements
	)
	{
		sge::parse::json::member_vector const &inner_members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				r
			).members
		);

		if(inner_members.size() != 1)
			throw exception(
				FCPPT_TEXT("inner members of the part array have to contain exactly one element!")
			);

		sge::parse::json::member const &member(
			inner_members[0]
		);

		fcppt::auto_ptr<
			part
		>
		to_insert(
			fcppt::make_auto_ptr<
				part
			>(
				sge::parse::json::get<
					sge::parse::json::object
				>(
					member.value_
				),
				global_parameters(
					path,
					ctx.textures(),
					cell_size,
					opt_delay,
					texture,
					ctx.sounds()
				)
			)
		);

		if(
			parts.insert(
				member.name,
				to_insert
			)
			.second == false
		)
			FCPPT_LOG_WARNING(
				log(),
				fcppt::log::_
					<< FCPPT_TEXT("Double insert in model!")
			);
	}
}