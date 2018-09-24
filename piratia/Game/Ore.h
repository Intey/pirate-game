#ifndef ORE_H
#define ORE_H

#include "Item.h"

namespace Game {

class Ore: public Item
{
public:
    enum class Type {
        Unknown,
        Cooper,
        Iron,
        Silver,
        Gold,
        Diamond
    };
    static std::string typeToString(Ore::Type t);
    static Type typeFromString(std::string const& typeName);
public:
    Ore() = default;
    Ore(Type t);
    Type type() const;

private:
    Type m_type = Type::Unknown;
};

} // namespace

#endif // ORE_H
