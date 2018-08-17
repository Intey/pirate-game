#ifndef PLAYER_H
#define PLAYER_H


class Player
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

#endif // PLAYER_H
