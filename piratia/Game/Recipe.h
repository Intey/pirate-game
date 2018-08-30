#ifndef RECIEPE_H
#define RECIEPE_H

#include <string>
#include <memory>
#include <vector>
#include <map>

#include "Item.h"
#include "structures.h"

namespace Game {

class Recipe
{
public:
    Recipe(std::string const& name, std::shared_ptr<Item> const& target,
            ItemPacks const& sources);

    ItemPacks sources() const;
    Item createTarget() const;

    std::string name() const;

    std::string getTargetName() const;

    bool operator==(Recipe const& other) const;

private:
    std::string m_name;
    ItemPacks m_sources;
    std::shared_ptr<Item> m_target;
};

} // namespace
#endif // RECIEPE_H
