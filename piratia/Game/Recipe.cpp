#include "Recipe.h"
#include "Item.h"

namespace Game {

Recipe::Recipe(const std::string &name, const std::shared_ptr<Item> &target,
                 const Recipe::ItemPacks &sources)
    : m_name(name), m_sources(sources), m_target(target)
{

}

Recipe::ItemPacks Recipe::sources() const
{
    return m_sources;
}

Item Recipe::createTarget() const
{
    return m_target->clone();

}

} // namespace
