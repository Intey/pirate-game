#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <game_core_export.h>

namespace Game {

class GAME_CORE_EXPORT Item
{
public:
    Item();
    Item(const std::string & name);
    virtual ~Item() = default;
    virtual std::string name() const;

    virtual Item clone() const;

    virtual operator bool() const;
    virtual bool operator==(Item const& o) const;
    virtual bool operator<(Item const& o) const;

private:
    std::string m_name;
};

} // namespace
#endif // ITEM_H
