#ifndef CRAFTABILITY_H
#define CRAFTABILITY_H

#include <memory>

namespace Game {

class Inventory;
class Reciepe;

/**
 * @brief Создает объект - удаляет объекты из инвентаря и добавляет в него созданный
 */
class CraftAbility
{
public:
    CraftAbility(std::shared_ptr<Inventory> const& inventory);
    bool craft(Reciepe const& reciepe) const;
private:
    std::shared_ptr<Inventory> m_inventory;
};


} // namespace
#endif // CRAFTABILITY_H
