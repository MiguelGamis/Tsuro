#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <QLabel>

class Player
{
public:
    std::vector<std::string> hand;
    int index;
    int row, column, slot, distance;
    bool isAlive = true;
    QLabel * piece;
    static int total;
    Player() {index = Player::total; Player::total++;}
};


#endif // PLAYER_H
