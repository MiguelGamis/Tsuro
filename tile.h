#ifndef TILE_H
#define TILE_H
#include <QLabel>
#include <QDebug>
#include <string>

#include <vector>
#include <QMessageBox>
#include <QPainter>

#include <player.h>
#include <deck.h>
#include <gamemanager.h>

class Tile: public QLabel
{
public:

    //Fields
    int row,col;
    std::string pathCode;
    std::string tileCode;
    int playerIndex;
    bool playable;
    int rotation = 0;
    std::map<int,std::string> paths;

    //Constructors
    Tile(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {};
    Tile(const QString& text, QWidget* pParent = 0, Qt::WindowFlags f = 0) : QLabel(text, pParent, f){};

    //Methods
    void mousePressEvent(QMouseEvent *event);
    void construct();
    void display();
    void tileDisplay();
};

#endif // TILE_H
