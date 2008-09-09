#ifndef SANGUIS_SERVER_ENTITIES_DECORATION_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_DECORATION_HPP_INCLUDED

#include "entity.hpp"
#include "../../decoration_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
class decoration : public entity
{
public:
decoration(base_parameters const &,decoration_type::type);
decoration_type::type type() const;
messages::auto_ptr add_message() const;
private:
decoration_type::type type_;
};
}
}
}

#endif