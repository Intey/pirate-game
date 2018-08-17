#include "Item.h"

namespace Game {

Item::Item(const std::string &name): m_name(name) {}

std::string Item::name() const
{
    return m_name;
}

Item Item::clone() const
{

}


} // namespace
