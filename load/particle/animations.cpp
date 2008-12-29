#include "animations.hpp"
#include "random_animation.hpp"
#include "animation.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include <sge/auto_ptr.hpp>
#include <sge/make_auto_ptr.hpp>

sanguis::load::particle::random_animation const &
sanguis::load::particle::animations::random() const
{
	return *random_animation_;
}

sanguis::load::particle::animations::animations(
	sge::path const &p,
	resource::context const &ctx)
{
	for(
		sge::directory_iterator it(p), end;
		it != end;
		++it)
	{
		if(!boost::filesystem::is_directory(*it))
		{
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< *it
					<< SGE_TEXT(" is not a directory!"));
			continue;
		}

		sge::auto_ptr<
			animation
		> anim(
			sge::make_auto_ptr<
				animation
			>(
				*it,
				ctx));

		animations_.push_back(
			anim);
	}

	if(animations_.empty())
		throw exception(
			SGE_TEXT("No animations found in ")
			+ p.string());
	
	sge::auto_ptr<
		random_animation
	> random_anim(
		sge::make_auto_ptr<
			random_animation
		>(
			animations_));

	random_animation_.take(
		random_anim);
}

sanguis::load::particle::animations::~animations()
{}
