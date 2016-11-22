#ifndef TILE_H
#define TILE_H
#include <QLabel>
#include <QDebug>
#include <string>

#include <player.h>
#include <vector>
#include <deck.h>
#include <QMessageBox>
#include <QPainter>

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

    //Constructors
    Tile(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {};
    Tile(const QString& text, QWidget* pParent = 0, Qt::WindowFlags f = 0) : QLabel(text, pParent, f){};

    //Methods
    void mousePressEvent(QMouseEvent *event);
    void display();
    void tileDisplay();
};

#endif // TILE_H
