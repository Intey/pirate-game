#include "Item.h"
#include <cassert>

namespace Game {

Item::Item()
{

}

Item::Item(const std::string &name): m_name(name) {
    assert(!name.empty() && "название предмета не может быть пустым");
}

std::string Item::name() const
{
    return m_name;
}

Item Item::clone() const
{
    auto item = Item(m_name);
    return item;
}

Game::Item::operator bool() const
{
    return m_name.empty();
}

bool Item::operator==(const Item &o) const
{
    return m_name == o.name();
}

bool Item::operator<(const Item &o) const
{
    return m_name < o.name();
}


} // namespace
