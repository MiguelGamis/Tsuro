#include "gamemanager.h"

extern std::vector<Player> players;
extern QWidget *myWidget;
extern Deck * deck;

int basepointsx[] = {100, 100};
int basepointsy[] = {100, 400};

void GameManager::showPlayerOnBoard(Player * p)
{
    for(int i = 0; i < 3; i++)
    {
        if(deck->moreCard())
        {
            std::string tile = deck->draw();
            p->addTileToHand(tile);
        }
    }

    QLabel *player1 = new QLabel(myWidget);
    QLabel *name1 = new QLabel("Player " +  QString::number(p->index + 1), myWidget);
    QLabel *time1 = new QLabel("00:00:00", myWidget);

    int basepointx = basepointsx[p->index];
    int basepointy = basepointsy[p->index];

    name1->setGeometry(basepointx + 25,basepointy + 110,80,20);
    time1->setGeometry(basepointx + 20,basepointy + 135,80,20);
    player1->setGeometry(basepointx,basepointy,100,100);
    player1->setPixmap(QPixmap(":/Graphics/profile.png"));
}

void GameManager::updateHand(Player * p)
{
    handtile * hand = p->hand;

    int i = 0;

     qInfo() << "Any cards?";

    while(hand)
    {
        qInfo() << "Here's a card!!! " + QString::fromStdString(hand->x);
        int basepointx = basepointsx[p->index];
        int basepointy = basepointsy[p->index];

        Tile * t = new Tile(myWidget);
        t->tileCode = hand->x;
        t->rotation = 0;
        t->playerIndex = p->index;
        t->playable = true;
        int gap = 0; if(i) gap = i*5;
        t->setGeometry(basepointx+(64*i)+gap, basepointy+150, 64, 64);
        t->construct();
        t->display();

        hand = hand->next; i++;
    }
}

