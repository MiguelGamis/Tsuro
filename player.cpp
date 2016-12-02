#include "player.h"

int Player::total = 0;

void Player::addTileToHand(std::string tile)
{
    handtile * newtile = new handtile();
    newtile->x = tile;
    newtile->next = this->hand;
    this->hand = newtile;
}

bool Player::removeFromHand(std::string tile)
{
    bool found = false;
    handtile *prev = NULL;
    handtile *ht = this->hand;
    while(ht)
    {
        if(ht->x.compare(tile) == 0)
        {
            if(!prev)
            {
                qInfo() << "FIRST TILE REMOVED";
                this->hand = ht->next;
            }
            else if(!ht->next)
            {
                qInfo() << "LAST TILE REMOVED";
                prev->next = NULL;
            }
            else
            {
                qInfo() << "MIDDLE TILE REMOVED";
                prev->next = ht->next;
            }

            found = true;
            break;
        }
        prev = ht;
        ht = ht->next;
    }
    return found;
}
