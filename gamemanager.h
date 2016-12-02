#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <tile.h>
#include <vector>
#include "player.h"
#include "deck.h"

class GameManager
{
public:
    static void showPlayerOnBoard(Player *p);
    static void updateHand(Player *p);
};

#endif // GAMEMANAGER_H
