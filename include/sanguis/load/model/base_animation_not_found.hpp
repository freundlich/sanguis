#ifndef SANGUIS_LOAD_MODEL_BASE_ANIMATION_NOT_FOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_BASE_ANIMATION_NOT_FOUND_HPP_INCLUDED

#include <sanguis/animation_type.hpp>
#include <sanguis/exception.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class base_animation_not_found
:
	public sanguis::exception
{
public:
	explicit base_animation_not_found(
		animation_type::type
	);

	animation_type::type
	anim_type() const;
private:
	animation_type::type anim_type_;
};

}
}
}

#endif