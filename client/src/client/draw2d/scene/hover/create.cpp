#include <sanguis/client/draw2d/entities/hover/name_and_health_fwd.hpp>
#include <sanguis/client/draw2d/entities/hover/info.hpp>
#include <sanguis/client/draw2d/entities/hover/weapon_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/hover/create.hpp>
#include <sanguis/client/draw2d/scene/hover/name_and_health.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/variant/apply_unary.hpp>


sanguis::client::draw2d::scene::hover::base_unique_ptr
sanguis::client::draw2d::scene::hover::create(
	sanguis::client::draw2d::scene::hover::parameters const &_parameters,
	sanguis::client::draw2d::entities::hover::info const &_info
)
{
	class visitor
	{
		FCPPT_NONASSIGNABLE(
			visitor
		);
	public:
		explicit
		visitor(
			sanguis::client::draw2d::scene::hover::parameters const &_nparameters
		)
		:
			parameters_(
				_nparameters
			)
		{
		}

		typedef
		sanguis::client::draw2d::scene::hover::base_unique_ptr
		result_type;

		result_type
		operator()(
			sanguis::client::draw2d::entities::hover::name_and_health const &_name_and_health
		) const
		{
			return
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::scene::hover::name_and_health
				>(
					parameters_,
					_name_and_health
				);
		}

		result_type
		operator()(
			sanguis::client::draw2d::entities::hover::weapon const &_weapon
		) const
		{
			return
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::scene::hover::weapon
				>(
					parameters_.gui_style(),
					parameters_.renderer(),
					parameters_.font(),
					parameters_.center(),
					parameters_.load_context(),
					_weapon
				);
		}
	private:
		sanguis::client::draw2d::scene::hover::parameters const &parameters_;
	};

	return
		fcppt::variant::apply_unary(
			visitor(
				_parameters
			),
			_info.get()
		);
}
