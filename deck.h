#ifndef DECK_H
#define DECK_H
#include <string>
#include <vector>
#include <Windows.h>
#include <QDebug>
#include <QDirIterator>

class Deck
{
public:
    std::string draw();
    void shuffle();
    void initialize();
    bool moreCard();
    void setCurrentTile(int n) {currentTile = n;}
    int getCurrentTile();
private:
    std::vector<std::string> contents;
    int currentTile = 0;
};

#endif // DECK_H
