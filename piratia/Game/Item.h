#ifndef ITEM_H
#define ITEM_H
#include <string>

namespace Game {

class Item
{
public:
    Item(const std::string & name);
    std::string name() const;

    Item clone() const;

private:
    std::string m_name;
};

} // namespace
#endif // ITEM_H
