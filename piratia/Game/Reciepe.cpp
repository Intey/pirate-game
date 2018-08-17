#include "Reciepe.h"
#include "Item.h"

namespace Game {

Reciepe::Reciepe(const std::string &name, const std::shared_ptr<Item> &target,
                 const std::vector<Item> &sources)
    : m_name(name), m_sources(sources), m_target(target)
{

}

std::vector<Item> Reciepe::sources() const
{
    return m_sources;
}

Item Reciepe::createTarget() const
{
    return m_target->clone();

}

} // namespace
