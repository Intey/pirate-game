#include "Recipe.h"
#include "Item.h"

namespace Game {

Recipe::Recipe(const std::string &name, const std::shared_ptr<Item> &target,
                 const ItemPacks &sources)
    : m_name(name), m_sources(sources), m_target(target)
{

}

ItemPacks Recipe::sources() const
{
    return m_sources;
}

Item Recipe::createTarget() const
{
    return m_target->clone();

}

std::string Recipe::name() const
{
    return m_name;
}

std::string Recipe::getTargetName() const
{
    return m_target->name();
}

bool Recipe::operator==(const Recipe &other) const
{
    return m_name == other.name() && *m_target == *other.m_target;
}

} // namespace
