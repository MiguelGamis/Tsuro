#include "deck.h"

void Deck::initialize()
{
    QDirIterator it(":/RedTiles", QStringList() << "*.png", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        //TODO: ROBUSTIFY
        std::string tile = it.next().toStdString() ;
        tile = tile.substr(12,8);
        this->contents.push_back(tile);
        currentTile++;
    }
}

void Deck::shuffle() // shuffles cards in deck
{
    for (int i = 0; i < currentTile; i++)
    {
        int randCard = rand() % currentTile;

        // swaps card with random card
        std::string swap = contents[i];
        contents[i] = contents[randCard];
        contents[randCard] = swap;
    }
}

std::string Deck::draw()
{
    std::string tilecode = contents[currentTile - 1];
    currentTile--;
    return tilecode;
}

bool Deck::moreCard()
{
    return currentTile != 0;
}

int Deck::getCurrentTile()
{
    return currentTile;
}
