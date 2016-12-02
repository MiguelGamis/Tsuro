#ifndef PLAYER_H
#define PLAYER_H

#include <QLabel>
#include <QDebug>

struct handtile {
  std::string x;
  handtile *next;
};

class Player
{
public:
    handtile * hand;
    int index;
    int row, column, slot, distance;
    bool isAlive = true;
    QLabel * piece;
    static int total;
    Player() {index = Player::total; Player::total++;}
    void addTileToHand(std::string tile);
    bool removeFromHand(std::string tile);
};


#endif // PLAYER_H
