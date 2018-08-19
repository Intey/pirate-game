#include "Reciepe.h"
#include "Item.h"

namespace Game {

Reciepe::Reciepe(const std::string &name, const std::shared_ptr<Item> &target,
                 const Reciepe::ItemPacks &sources)
    : m_name(name), m_sources(sources), m_target(target)
{

}

Reciepe::ItemPacks Reciepe::sources() const
{
    return m_sources;
}

Item Reciepe::createTarget() const
{
    return m_target->clone();

}

} // namespace
