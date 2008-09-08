#include "hud.hpp"
#include <sge/font/font.hpp>
#include <sge/format.hpp>
#include <sge/text.hpp>

sanguis::draw::hud::hud(
	sge::font::font &font)
: font(font),
  experience_(0)
{}

void sanguis::draw::hud::experience(
	messages::exp_type const nexperience)
{
	experience_ = nexperience;
}

void sanguis::draw::hud::update(
	time_type)
{
	font.draw_text((
		sge::format(
			SGE_TEXT("exp: %1%"))
			% experience_)
			.str(),
		sge::font::pos(0, 0),
		sge::font::dim(100, 100), // FIXME
		sge::font::align_h::left,
		sge::font::align_v::top);
}
