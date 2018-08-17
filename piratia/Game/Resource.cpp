#include "Resource.h"
namespace Game {

Resource::Resource(int count, const std::string &name)
    :Item(name), m_count(count)
{

}

} // namespace
