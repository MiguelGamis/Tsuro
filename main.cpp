#include "mainwindow.h"
//#include "gamemanager.h"
#include "player.h"
#include "deck.h"
#include "tile.h"
#include <QApplication>
#include <QLabel>
#include <vector>
#include <iostream>
#include <QStyle>

QWidget *myWidget;

Tile *tile[6][6] = { { NULL } };
Tile *click1;

class Border
{
public:
    Border();
    void outline(QWidget *baseWidget, int xPos, int yPos, int Pos)
    {
         QLabel *outLabel = new QLabel(baseWidget);

        if(!Pos)
            outLabel->setGeometry(xPos,yPos,424,20);        //Horizontal Borders

        else
            outLabel->setGeometry(xPos,yPos,20,384);        //Vertical Borders

        outLabel->setStyleSheet("QLabel { background-color :rgb(170, 170, 127); color : black; }");
    }
};

//class Player
//{
//public:
//    std::vector<std::string> hand;
//    int index;
//    int row, column, slot;
//    static int total;
//    Player() {index = Player::total; Player::total++;}
//};

//int Player::total = 0;

std::vector<Player> players;
int turn;

Deck * deck = new Deck();

int basepointsx[] = {100, 100};
int basepointsy[] = {100, 400};

void showPlayers(QWidget *baseWidget)
{
    for(int p = 0; p < players.size(); p++)
    {
        for(int i = 0; i < 3; i++)
        {
            if(deck->moreCard())
            {
                std::string tile = deck->draw();
                players[p].hand.push_back(tile);
            }
        }

        QLabel *player1 = new QLabel(baseWidget);
        QLabel *name1 = new QLabel("Player", baseWidget);
        QLabel *time1 = new QLabel("00:00:00", baseWidget);

        int basepointx = basepointsx[players[p].index];
        int basepointy = basepointsy[players[p].index];

        name1->setGeometry(basepointx + 25,basepointy + 110,80,20);
        time1->setGeometry(basepointx + 20,basepointy + 135,80,20);
        player1->setGeometry(basepointx,basepointy,100,100);
        player1->setPixmap(QPixmap(":/Graphics/profile.png"));
    }
}

void updateHand()
{
    for(int p = 0; p < players.size(); p++)
    {
        qInfo() << "Player hand";
        for(int i = 0; i < players[p].hand.size(); i++)
        {
            int basepointx = basepointsx[players[p].index];
            int basepointy = basepointsy[players[p].index];

            Tile * t = new Tile(myWidget);
            t->tileCode = players[p].hand[i];
            qInfo() << QString::fromStdString(t->tileCode);
            t->rotation = 0;
            t->playerIndex = p;
            t->playable = true;
            int gap = 0; if(i) gap = i*5;
            t->setGeometry(basepointx+(64*i)+gap, basepointy+150, 64, 64);
            t->construct();
            t->display();
        }
    }
}

QLabel *selectedTile;

void accessories(QWidget *baseWidget)
{
    showPlayers(baseWidget);
    
    
    QLabel *moves = new QLabel(baseWidget);

    moves->setGeometry(1000,105,250,550);
    moves->setStyleSheet("QLabel {background-color: white;}");

    selectedTile = new QLabel("None", baseWidget);
    selectedTile->setGeometry(1000, 95, 80, 20);
}

void tsuroBoard(QWidget *baseWidget, Tile *tile[6][6])
{
    int i,j=0,hor,ver;
    Border *border[4]={ NULL };

    QFrame * board = new QFrame(baseWidget);
    board->setGeometry(340,115,405,405);
    board->setStyleSheet("QFrame {background-image: url(:/Graphics/BoardBackground.jpg)}");

    //borderDisplay
//    {
//    border[0]->outline(baseWidget,330,105,0);
//    border[1]->outline(baseWidget,330,504,0);
//    border[2]->outline(baseWidget,330,125,1);
//    border[2]->outline(baseWidget,729,125,1);
//    }

    //Create 64 tiles (allocating memories to the objects of Tile class)
    ver=125;
    for(i=0;i<6;i++)
    {
        hor=350;
        for(j=0;j<6;j++)
        {
            tile[i][j] = new Tile(baseWidget);
            tile[i][j]->row=i;
            tile[i][j]->col=j;
            //tile[i][j]->tileDisplay();
            tile[i][j]->setGeometry(hor,ver,64,64);
            tile[i][j]->playable = false;
            hor+=64;
        }
        ver+=64;
    }
}

void drawPlayers()
{
//    QPainter painter;
//    painter.setRenderHint( QPainter::Antialiasing );
//    painter.setPen( Qt::black );
//    painter.drawEllipse(200,105,100,100);

    for(int p = 0; p < players.size(); p++)
    {
        int row = players[p].row;
        int column = players[p].column;
        int slot = players[p].slot;
        int deltax = 0;
        int deltay = 0;

        QLabel *circle = new QLabel(myWidget);
        players[p].piece = circle;
        switch(slot)
        {
            case 1:
                deltax = 21;
                break;
            case 2:
                deltax = 42;
                break;
            case 3:
                deltax = 64;
                deltay = 21;
                break;
            case 4:
                deltax = 64;
                deltay = 42;
                break;
            case 5:
                deltax = 42;
                deltay = 64;
                break;
            case 6:
                deltax = 21;
                deltay = 64;
                break;
            case 7:
                deltay = 42;
                break;
            case 8:
                deltay = 21;
                break;
        }

        circle->setGeometry(345 + (column*64) + deltax, 120 + (row*64) + deltay, 10, 10);
        circle->setStyleSheet("QLabel {background-color: rgb(100,55,127);}:hover{background-color: rgb(170,85,127);}");
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myWidget = new QWidget();
    myWidget->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            myWidget->size(),
            QRect(0,0,2000,1000)
        )
    );

    deck->initialize();
    deck->shuffle();

    Player p1, p2;
    //HARD-CODE LOCATIONS
    p1.row = 0; p1.column = 0; p1.slot = 1;
    p2.row = 2; p2.column = 0; p2.slot = 8;

    players.push_back(p1);
    players.push_back(p2);
    turn = 0;//rand()%players.size();

    accessories(myWidget);
    updateHand();
    tsuroBoard(myWidget,tile);
    drawPlayers();

    myWidget->show();
    return a.exec();
}
