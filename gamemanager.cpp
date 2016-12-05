#include "gamemanager.h"

extern std::vector<Player> players;
extern QWidget *myWidget;
extern Deck * deck;
extern Tile *hands[6][8];

int basepointsx[] = {100, 100};
int basepointsy[] = {100, 400};

int maxHand = 8;
int maxPlayers = 6;
int tilemargin = 5;

void GameManager::setUpTileSlot()
{
    qInfo() << "THERE ARE " + QString::number(players.size()) + " PLAYERS";
    for(int playerindex = 0; playerindex < players.size(); playerindex++)
    {
        qInfo() << "MAKING TILE SLOTS FOR PLAYER " + QString::number(playerindex);
        int basepointx = basepointsx[playerindex];
        int basepointy = basepointsy[playerindex];

        for(int tileindex = 0; tileindex < maxHand; tileindex++)
        {
            qInfo() << "    TILE SLOT #" + QString::number(tileindex);
            Tile * t = new Tile(myWidget);

            t->setGeometry( basepointx + (64*tileindex) + (tileindex*tilemargin),
                            basepointy + 150,
                            64,
                            64);

            hands[playerindex][tileindex] = t;
        }
    }
}

void GameManager::showPlayerOnBoard(Player * p)
{
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

    qInfo() << "Updating hand of PLAYER " + QString::number(p->index) + " with 1st tile " + QString::fromStdString(p->hand->x);

    int i = 0;

    while(hand)
    {
        qInfo() << "Updating handtile [" + QString::number(p->index) + "][" + QString::number(i) + "]";

        qInfo() << QString::fromStdString(hand->x);

        hands[p->index][i]->tileCode = hand->x;

        hands[p->index][i]->rotation = 0;
        hands[p->index][i]->playerIndex = p->index;
        hands[p->index][i]->playable = true;
        hands[p->index][i]->paths.clear();
        hands[p->index][i]->construct();
        hands[p->index][i]->display();

        hand = hand->next; i++;
    }
}
