#include "animations.hpp"
#include "textures.hpp"
#include "map_get_or_create.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/time/millisecond.hpp>
#include <sge/time/duration.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/is_directory.hpp>
#include <fcppt/filesystem/is_regular.hpp>
#include <fcppt/filesystem/next_file.hpp>
#include <fcppt/filesystem/first_file.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>

sanguis::load::resource::animation::series const
sanguis::load::resource::animations::load(
	fcppt::filesystem::path const &dir) const
{
	return map_get_or_create(
		animations_,
		dir, 
		std::tr1::bind(
			&animations::do_load,
			this,
			std::tr1::placeholders::_1
		)
	);
}

sanguis::load::resource::animations::animations(
	textures &_textures
)
:
	textures_(_textures)
{
}

sanguis::load::resource::animations::~animations()
{
}

sanguis::load::resource::animation::series const
sanguis::load::resource::animations::do_load(
	fcppt::filesystem::path const &dir) const
{
	if (!fcppt::filesystem::exists(dir) || !fcppt::filesystem::is_directory(dir))
		throw exception(
			FCPPT_TEXT("directory for animation \"")
			+ fcppt::filesystem::path_to_string(
				dir
			)
			+ FCPPT_TEXT("\" doesn't exist")
		);

	fcppt::filesystem::path const framesfile = dir / FCPPT_TEXT("frames");

	// look for frames file inside directory
	if (!fcppt::filesystem::exists(framesfile) || !fcppt::filesystem::is_regular(framesfile))
		return load_without_frames_file(dir);
	//
	// and parse line by line
	fcppt::io::ifstream file(framesfile);
	if (!file.is_open())
		throw exception(
			FCPPT_TEXT("error opening file \"")
			+ fcppt::filesystem::path_to_string(
				framesfile
			)
			+ FCPPT_TEXT("\""));
	
	// read first line, determine if it has constant frame time
	fcppt::string line;
	if (!std::getline(file,line))
		throw exception(
			FCPPT_TEXT("unexpected end of file \"")
			+ fcppt::filesystem::path_to_string(
				framesfile
			)
		);

	fcppt::optional<
		sge::time::duration
	> const_delay;

	if (boost::algorithm::starts_with(line,FCPPT_TEXT("frame_length ")))
		const_delay =
			sge::time::millisecond(
				fcppt::lexical_cast<
					sge::time::unit
				>(
					line.substr(
						fcppt::string(
							FCPPT_TEXT("frame_length ")
						)
						.length()
					)
				)
			);
	else
		file.seekg(0, std::ios_base::beg);
	
	animation::series anim;

	unsigned lineno = const_delay ? 2 : 1;
	while (std::getline(file,line))
	{
		boost::algorithm::trim(line);

		if (line.empty())
			continue;

		sge::time::duration delay(0);
		fcppt::string filename = line;

		if (!const_delay)
		{
			fcppt::io::istringstream ss(line);
			sge::time::unit temp_delay;
			ss >> temp_delay >> std::ws;
			if (!ss)
				throw exception(
					FCPPT_TEXT("invalid line ")
					+ fcppt::lexical_cast<fcppt::string>(lineno)
					+ FCPPT_TEXT(" in animation ")
					+ fcppt::filesystem::path_to_string(
						dir
					)
				);
			filename =
				ss.str().substr(
					static_cast<
						fcppt::string::size_type
					>(
						ss.tellg()
					)
				);
			delay = sge::time::millisecond(temp_delay);
		}
		else
		{
			delay = *const_delay;
		}

		anim.push_back(
			animation::entity(
				delay,
				load_texture(
					dir / filename
				)
			)
		);

		++lineno;
	}
		
	return anim;
}

sge::texture::const_part_ptr const
sanguis::load::resource::animations::load_texture(
	fcppt::filesystem::path const &p) const
{
	return textures_.do_load_inner(p);	
}

sanguis::load::resource::animation::series const
sanguis::load::resource::animations::load_without_frames_file(
	fcppt::filesystem::path const &dir) const
{
	fcppt::filesystem::directory_iterator const first_file(
		fcppt::filesystem::first_file(
			dir));
	
	if(first_file == fcppt::filesystem::directory_iterator())
		throw sanguis::exception(
			fcppt::filesystem::path_to_string(
				dir
			)
			+ FCPPT_TEXT(" is empty!")
		);
	
	fcppt::filesystem::path const first_path(
		*first_file);

	if(fcppt::filesystem::next_file(first_file) != fcppt::filesystem::directory_iterator())
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("No frames file found in \"")
				<< fcppt::filesystem::path_to_string(
					dir
				)
				<< FCPPT_TEXT("\" although there is more than one file!")
				<< FCPPT_TEXT(" Just taking the first image."));

	animation::series ret;
	ret.push_back(
		animation::entity(
			sge::time::millisecond(
				static_cast<sge::time::unit>(1)),
			load_texture(first_path)
		)
	);
	return ret; // TODO: can we do this with boost::assign?
}
