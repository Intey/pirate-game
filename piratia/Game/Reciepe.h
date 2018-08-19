#ifndef RECIEPE_H
#define RECIEPE_H

#include <string>
#include <memory>
#include <vector>
#include <map>

namespace Game {

class Item;

class Reciepe
{
public:
    using ItemPacks=std::map<Item, int>;
public:
    Reciepe(std::string const& name, std::shared_ptr<Item> const& target,
            ItemPacks const& sources);

    ItemPacks sources() const;
    Item createTarget() const;

private:
    std::string m_name;
    ItemPacks m_sources;
    std::shared_ptr<Item> m_target;
};

} // namespace
#endif // RECIEPE_H
