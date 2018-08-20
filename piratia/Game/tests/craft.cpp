#include "../Recipe.h"
#include "../Inventory.h"
#include "../CraftAbility.h"
#include <cassert>
#include <iostream>

using namespace std;
using namespace Game;

void expect(bool valid, std::string const& message)
{
    string result = (valid? "PASS": "FAILED");
    cout << message << " : " << result << endl;
}

template<typename T1, typename T2>
void expectEq(const T1 left, const T2 right, std::string const& message) {
    expect(left == right, message);
    if (left != right)
        cout << left << " == " << right << endl;
}

void testEmptyInventoryCraft()
{
    Item ironIgnot { "iron ignot" };
    Item wood { "wood" };

    std::shared_ptr<Inventory> inventory { new Inventory() };
    inventory->addItem(wood);

    std::shared_ptr<Item> target { new Item("Sword") };
    Recipe::ItemPacks sources;
    sources[ironIgnot] = 4;
    sources[wood] = 1;

    Recipe recipe {"simple sword", target, sources };

    // проверяем, что ресурсов хватит. Чтобы показывать возможность крафта того или иного рецепта
    expect(!inventory->has(sources),
          "должно быть проверено, что в инвентаре нет ресурсов");

    CraftAbility ability { inventory };
    auto required_resources = inventory->diff(recipe.sources());
    expectEq(required_resources[ironIgnot], 4,
          "по рецепту нужно 4 железных слитка");
    expect(required_resources.find(wood) == required_resources.end(),
          "ресурс который есть в инвентаре не должен запрашиваться");
}

void testMatchingInventory()
{
    std::shared_ptr<Inventory> inventory { new Inventory };
    CraftAbility ability { inventory };
    std::shared_ptr<Item> target { new Item("Sword") };
    Item ironIgnot { "iron ignot" };
    Item wood { "wood" };
    Recipe::ItemPacks sources;
    for (int i = 0; i < 4; ++i) {
        inventory->addItem(ironIgnot);
    }
    inventory->addItem(wood);
    sources[ironIgnot] = 4;
    sources[wood] = 1;

    Recipe recipe {"simple sword", target, sources };

    // проверяем, что ресурсов хватит. Чтобы показывать возможность крафта того или иного рецепта
    auto resultItem = ability.craft(recipe);
    expectEq(resultItem, *target,
             "когда ресурсов хватает, должен создаваться предмет");
}

int main(int argc, char *argv[])
{
    testEmptyInventoryCraft();
    testMatchingInventory();
    return 0;
}
