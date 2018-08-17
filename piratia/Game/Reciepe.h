#ifndef RECIEPE_H
#define RECIEPE_H

#include <string>
#include <memory>
#include <vector>

namespace Game {

class Item;

class Reciepe
{
public:
    Reciepe(std::string const& name, std::shared_ptr<Item> const& target, std::vector<Item> const& sources);
    std::vector<Item> sources() const;
    Item createTarget() const;

private:
    std::string m_name;
    std::vector<Item> m_sources;
    std::shared_ptr<Item> m_target;
};

} // namespace
#endif // RECIEPE_H
