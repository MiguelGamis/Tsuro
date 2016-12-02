#include "mainwindow.h"
#include "gamemanager.h"
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

GameManager *gm;

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

std::vector<Player> players;
int turn;

Deck * deck = new Deck();

void showPlayersOnBoard()
{
    for(int p = 0; p < players.size(); p++)
    {
        GameManager::showPlayerOnBoard(&players[p]);
    }
}

void updateHand()
{
    for(int p = 0; p < players.size(); p++)
    {
        GameManager::updateHand(&players[p]);
    }
}

QLabel *selectedTile;

void accessories(QWidget *baseWidget)
{
    showPlayersOnBoard();
    
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
        std::string tile = ":/Graphics/blue.png";
        QString qtile = QString::fromStdString(tile);
        QPixmap tileimg = QPixmap(qtile);
        QMatrix m; m.scale(0.1,0.1);
        tileimg = tileimg.transformed(m);
        circle->setPixmap(tileimg);
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

        circle->setGeometry(345 + (column*64) + deltax, 113 + (row*64) + deltay, 20, 30);
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
            QRect(0,0,2000,1200)
        )
    );

    deck->initialize();
    deck->shuffle();

    Player p1, p2;
    //HARD-CODE LOCATIONS
    p1.row = 0; p1.column = 0; p1.slot = 1; p1.index = 0;
    p2.row = 2; p2.column = 0; p2.slot = 8; p2.index = 1;

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
