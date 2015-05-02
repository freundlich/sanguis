#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/impl/serialize/image_name.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/optional_member.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/text.hpp>


sge::parse::json::optional_member
sanguis::model::impl::serialize::image_name(
	sanguis::model::optional_image_name const &_opt_name
)
{
	return
		fcppt::optional_bind_construct(
			_opt_name,
			[](
				sanguis::model::image_name const &_name
			)
			{
				return
					sge::parse::json::member(
						FCPPT_TEXT("texture"),
						_name.get()
					);
			}
		);
}