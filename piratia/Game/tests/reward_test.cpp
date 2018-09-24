#include <test_core.h>
#include <Player.h>
#include <Inventory.h>
#include <Reward.h>
#include <Ore.h>
#include <FindPairGame.h>

using namespace Game;
using namespace std;

void testRewardGotton() {

    auto player = Player::getInstance();

    FindPairGame game(2, 10);

    Reward rwd;
    rwd.add("Cooper", 10);
    rwd.add("Iron", 10);
    player->ownReward(rwd);
    auto inventory = player->getInventory();

    Ore cooper(Ore::Type::Cooper);
    Ore iron(Ore::Type::Iron);

    expect(inventory->has({{cooper, 10}}), "inventory should have 10 cooper");
    expect(inventory->has({{iron, 10}}), "inventory should have 10 cooper");



}
int main(int argc, char *argv[])
{
    testRewardGotton();
    return 0;
}
