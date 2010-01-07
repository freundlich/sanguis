#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_PART_INDEX_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_PART_INDEX_HPP_INCLUDED

#include <cstddef>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

class index
{
public:
	typedef std::size_t value_type;

	explicit sprite_part_index(
		value_type
	);
	
	value_type
	get() const;
private:
	value_type value;
};

}
}
}
}

#endif