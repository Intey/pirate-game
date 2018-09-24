#include "Ore.h"

namespace Game {
std::string Ore::typeToString(Ore::Type t) {
    switch (t) {
    case Ore::Type::Cooper:
        return "Cooper";
    case Ore::Type::Iron:
        return "Iron";
    case Ore::Type::Silver:
        return "Silver";
    case Ore::Type::Gold:
        return "Gold";
    case Ore::Type::Diamond:
        return "Diamond";
    default:
        return "Unknown";
    }
}

Ore::Type Ore::typeFromString(const std::string &typeName)
{
    if (typeName == "Cooper") return Ore::Type::Cooper;
    else if (typeName == "Iron") return Ore::Type::Iron;
    else if (typeName == "Silver") return Ore::Type::Silver;
    else if (typeName == "Gold") return Ore::Type::Gold;
    else if (typeName == "Diamond") return Ore::Type::Diamond;
    else return Ore::Type::Unknown;
}


Ore::Ore(Ore::Type t): Item(Ore::typeToString(t)), m_type(t)
{

}

Ore::Type Ore::type() const
{
    return m_type;
}

} // namespace
