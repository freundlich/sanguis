#include "friend.hpp"
#include "../entities/model/object.hpp"
#include "../entities/sentry.hpp"
#include "../z_ordering.hpp"
#include "../../../load/friend_name.hpp"
#include "../../../friend_type.hpp"
#include "../../../exception.hpp"
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::friend_(
	entities::model::parameters const &_param,
	friend_type::type const _etype
)
{
	switch(
		_etype
	)
	{
	case friend_type::size:
		break;
	case friend_type::spider:
		return
			entities::unique_ptr(
				fcppt::make_unique_ptr<
					entities::model::object
				>(
					fcppt::cref(
						_param
					),
					load::friend_name(
						_etype
					),
					z_ordering::model_generic,
					entities::model::needs_healthbar::yes,
					entities::model::decay_option::delayed
				)
			);
	case friend_type::sentry:
		return
			entities::unique_ptr(
				fcppt::make_unique_ptr<
					entities::sentry
				>(
					fcppt::cref(
						_param
					)
				)
			);
	}

	throw sanguis::exception(
		FCPPT_TEXT("Missing factory code in client::draw2d::factory::friend!")
	);
}
