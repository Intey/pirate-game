#ifndef RESOURCE_H
#define RESOURCE_H

#include "Item.h"
#include <game_core_export.h>

namespace Game {

class GAME_CORE_EXPORT Resource: public Item {
public:
    Resource(int count, std::string const& name);
private:
    int m_count;
};
} // namespace
#endif // RESOURCE_H
