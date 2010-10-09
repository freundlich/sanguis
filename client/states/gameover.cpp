#include "gameover.hpp"
#include "menu.hpp"
#include "../perk_cast.hpp"
#include "../../media_path.hpp"
#include "../../messages/create.hpp"
#include "../../resolution_type.hpp"
#include "../events/menu.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"
#include "../cursor/object.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/make_image.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/grid.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/image/loader.hpp>
#include <sge/renderer/device.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/dim.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/algorithm/join_strings.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

namespace
{

sge::gui::dim const
dialog_size(
	sanguis::resolution_type const &resolution_
)
{
	float const
		scale_x = 0.5f,
		scale_y = 0.8f;
	
	return
		sge::gui::dim(
			static_cast<sge::gui::unit>(
				static_cast<float>(
					resolution_.w()
				)
				* scale_x
			),
			static_cast<sge::gui::unit>(
				static_cast<float>(
					resolution_.h()
				)
				* scale_y
			)
		);
}

sge::gui::point const
dialog_pos(
	sanguis::resolution_type const &resolution_
)
{
	return 
		fcppt::math::dim::structure_cast<sge::gui::point>(
			resolution_
		) /
		static_cast<sge::gui::unit>(2)-
		fcppt::math::dim::structure_cast<sge::gui::point>(
			dialog_size(
				resolution_
			)
		) /
		static_cast<sge::gui::unit>(2);
}
}

sanguis::client::states::gameover::gameover(
	my_context ctx
)
:
	my_base(ctx),
	m_(
		context<machine>().renderer(),
		context<machine>().input_processor(),
		sge::gui::skins::ptr(
			new sge::gui::skins::standard(
				context<machine>().font_metrics()
			)
		),
		context<machine>().cursor()
	),
	background_(
		m_,
		sge::gui::widgets::parameters()
			.pos(
				dialog_pos(
					context<machine>().renderer()->screen_size()
				)
			)
			.size(
				dialog_size(
					context<machine>().renderer()->screen_size()
				)
			)
			.layout(
				fcppt::make_shared_ptr<sge::gui::layouts::grid>()
			)
	),
	dead_label(
		background_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,0)),
		FCPPT_TEXT("You are dead.")
	),
	score(
		background_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,1)
			)
			.layout(
				fcppt::make_shared_ptr<sge::gui::layouts::grid>()
			)
	),
	names_head(
		score,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,0)
			),
		FCPPT_TEXT("Name(s):")
	),
	score_head(
		score,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(1,0)
			),
		FCPPT_TEXT("Score:")
	),
	names_text(
		score,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,1)
			),
		fcppt::algorithm::join_strings(
			context<machine>().gameover_names(),
			FCPPT_TEXT(", ")
		)
	),
	score_text(
		score,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(1,1)
			),
		fcppt::lexical_cast<fcppt::string>(
			context<machine>().gameover_score()
		)
	),
	buttons_return(
		background_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,2)
			),
		FCPPT_TEXT("Main menu")
	),
	return_connection(
		buttons_return.register_clicked(
			std::tr1::bind(
				&gameover::return_clicked,
				this
			)
		)
	)
{
	context<machine>().cursor()->visible(true);
}

boost::statechart::result
sanguis::client::states::gameover::react(
	events::tick const &
)
{
	context<machine>().dispatch();

	m_.update();

	m_.draw();

	return discard_event();
}

boost::statechart::result
sanguis::client::states::gameover::react(
	events::menu const &
)
{
	return transit<menu>();
}


boost::statechart::result
sanguis::client::states::gameover::react(
	events::message const &m
)
{
	return handle_default_msg(
		*m.value()
	);
}

boost::statechart::result
sanguis::client::states::gameover::handle_default_msg(
	messages::base const &
)
{
	return discard_event();
}

void
sanguis::client::states::gameover::return_clicked()
{
	post_event(
		events::menu()
	);
}
