#ifndef PLAYER_H
#define PLAYER_H
#include <game_core_export.h>


namespace Game {

class GAME_CORE_EXPORT Player
{
public:
    static Player* getInstance();
private:
    int m_score;

//singleton часть
private:
    Player() noexcept;
    Player(Player const& other) = delete;
    Player operator=(Player const& other) = delete;
    ~Player();
};

} // namespace
#endif // PLAYER_H
