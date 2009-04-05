#include "paused.hpp"
#include "unpaused.hpp"
#include "../from_perk_type.hpp"
#include "../../media_path.hpp"
#include "../../dispatch_type.hpp"
#include "../../messages/unpause.hpp"
#include "../../resolution.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../messages/available_perks.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/make_image.hpp>
#include <sge/image/loader.hpp>
#include <sge/systems/instance.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/ref.hpp>

namespace
{
sge::gui::dim const dialog_size()
{
	float const scale_x = 0.4f,
	            scale_y = 0.8f;
	
	return sge::gui::dim(
		static_cast<sge::gui::unit>(
			static_cast<float>(
				sanguis::resolution().w())*scale_x),
		static_cast<sge::gui::unit>(
			static_cast<float>(
				sanguis::resolution().h())*scale_y));
}

sge::gui::point const dialog_pos()
{
	return 
		sge::structure_cast<sge::gui::point>(
			sanguis::resolution())/
		static_cast<sge::gui::unit>(2)-
		sge::structure_cast<sge::gui::point>(
			dialog_size())/
		static_cast<sge::gui::unit>(2);
}
}

sanguis::client::states::paused::paused(my_context ctx)
	: my_base(ctx),
		m_(
			context<machine>().sys().renderer(),
			context<machine>().sys().image_loader(),
			context<machine>().sys().input_system(),
			context<machine>().sys().font_system(),
			sge::gui::skin_ptr(
				new sge::gui::skins::standard())),
		background_(
			m_,
			sge::gui::widget::parameters()
				.pos(
					dialog_pos())
				.size(
					dialog_size())),
		perks_left_(
			background_,
			sge::gui::widget::parameters(),
			SGE_TEXT("Perks left: ")),
		buttons_(),
		connections_()
{
	context<running>().pause(true);
	regenerate_widgets();
}

boost::statechart::result
sanguis::client::states::paused::react(
	tick_event const &t)
{
	context<running>().process(t.delta());
	context<running>().draw(t.delta());
	m_.draw();
	return discard_event();
}

boost::statechart::result
sanguis::client::states::paused::react(
	message_event const &m)
{
	return dispatch_type<
		boost::mpl::vector<
			messages::unpause,
			messages::available_perks
		>,
		boost::statechart::result>(
		*this,
		*m.message,
		boost::bind(&paused::handle_default_msg, this, _1));
}

boost::statechart::result sanguis::client::states::paused::operator()(
	messages::unpause const &)
{
	return transit<unpaused>();
}

boost::statechart::result sanguis::client::states::paused::operator()(
	messages::available_perks const &)
{
	regenerate_widgets();
	return forward_event();
}

boost::statechart::result sanguis::client::states::paused::handle_default_msg(
	messages::base const &)
{
	return forward_event();
}

void sanguis::client::states::paused::regenerate_widgets()
{
	perks_left_.text(
			SGE_TEXT("Perks left: ")+
			sge::lexical_cast<sge::string>(
				context<running>().levels_left()));
	buttons_.clear();
	sge::filesystem::path const p = media_path()/SGE_TEXT("perks");
	BOOST_FOREACH(running::perk_container::const_reference r,context<running>().perks())
	{
		sge::filesystem::path const base = 
			p/from_perk_type(r);

		sge::gui::image_ptr const 
			normal_image = 
				sge::gui::make_image(
					context<machine>().sys().image_loader()->load(
						base/
						SGE_TEXT("normal.png"))),
			hover_image = 
				sge::gui::make_image(
					context<machine>().sys().image_loader()->load(
						base/
						SGE_TEXT("hover.png")));

		buttons_.push_back(
			new sge::gui::widgets::buttons::image(
				background_,
				sge::gui::widget::parameters(),
				normal_image,
				hover_image,
				hover_image,
				hover_image));

		connections_.connect(
			buttons_.back().register_clicked(
				boost::bind(
					&paused::perk_callback,
					this,
					boost::ref(r))));
	}
}

void sanguis::client::states::paused::perk_callback(
	perk_type::type const p)
{
	context<machine>().send(
		messages::auto_ptr(
			new messages::player_choose_perk(
				context<running>().player_id(),
				p)));
	context<running>().consume_level();
}
