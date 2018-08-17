#ifndef RESOURCE_H
#define RESOURCE_H

#include "Item.h"

namespace Game {

class Resource: public Item {
public:
    Resource(int count, std::string const& name);
private:
    int m_count;
};
} // namespace
#endif // RESOURCE_H
