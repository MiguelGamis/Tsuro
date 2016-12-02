#include "tile.h"

//extern int count,turn;
extern QWidget *myWidget;
extern Tile *click1;
extern Tile *tile[6][6];
extern int turn;
extern QLabel *selectedTile;

extern std::vector<Player> players;
extern Deck * deck;
extern int basepointsx[];
extern int basepointsy[];

void validate(Tile *temp);//,int c);

void drawPlayer(Player * player)
{
    int deltax = 0;
    int deltay = 0;

    switch(player->slot)
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

    int x_ = 345 + (player->column*64) + deltax;
    int y_ = 113 + (player->row*64) + deltay;
    player->piece->setGeometry(x_, y_, 20, 30);

    if(!player->isAlive) QMessageBox::information(myWidget, "Player Eliminated", "Player " + QString::number(player->index + 1) + " has been eliminated");
}

void movePlayers(Tile * t)
{
    for(int p = 0; p < players.size(); p++)
    {
        if(!players[p].isAlive)
        {
            continue;
        }
        if(players[p].row == t->row && players[p].column == t->col)
        {
            Tile * currentTile = t;

            do
            {
                int slot = players[p].slot;
                char x = currentTile->pathCode.at(slot-1);
                int route = x - '0';

                //CHECK FOR COLLISION
                bool isColliding = false;
                for(int p2 = p+1; p2 < players.size(); p2++)
                {
                    bool samerow = players[p].row == players[p2].row;
                    bool samecolumn = players[p].column == players[p2].column;
                    if(samerow && samecolumn)
                    {
                        bool samepath = route == players[p2].slot;
                        if(samepath)
                        {
                            players[p].isAlive = false;
                            players[p2].isAlive = false;
                            isColliding = true;
                            break;
                        }
                    }
                }

                if(isColliding) {currentTile->display(); break;}

                qInfo() << QString::number(slot) + "th of " + QString::fromStdString(currentTile->pathCode) + " = " + QString::number(route);

                switch(route)
                {
                    case 1:
                        qInfo() << "UP to slot 6...";
                        players[p].slot = 6;
                        players[p].row--;
                        break;
                    case 2:
                        qInfo() << "UP to slot 5...";
                        players[p].slot = 5;
                        players[p].row--;
                        break;
                    case 3:
                        qInfo() << "> to slot 8";
                        players[p].slot = 8;
                        players[p].column++;
                        break;
                    case 4:
                        qInfo() << "> to slot 7...";
                        players[p].slot = 7;
                        players[p].column++;
                        break;
                    case 5:
                        qInfo() << "DOWN to slot 2...";
                        players[p].slot = 2;
                        players[p].row++;
                        break;
                    case 6:
                        qInfo() << "DOWN to slot 1...";
                        players[p].slot = 1;
                        players[p].row++;
                        break;
                    case 7:
                        qInfo() << "< to slot 4...";
                        players[p].slot = 4;
                        players[p].column--;
                        break;
                    case 8:
                        qInfo() << "< to slot 3...";
                        players[p].slot = 3;
                        players[p].column--;
                        break;
                }

                qInfo() << "Player at (" + QString::number(players[p].row) + ", " + QString::number(players[p].column) + ")";

                std::map<int, std::string>::iterator g;
                for(g = currentTile->paths.begin(); g != currentTile->paths.end(); g++) {
                    qInfo() << "[" + QString::number(g->first);// + "] -> " + p->second;
                }

                char color;
                switch(p)
                {
                    case 0:
                        color = 'b';
                        break;
                    case 1:
                        color = 'r';
                        break;
                }

                //FIND CORRECT PATH
                int _route = (route-1) - 2*currentTile->rotation; if(_route < 0) _route += 8; _route += 1;
                int _slot = (slot-1) - 2*currentTile->rotation; if(_slot < 0) _slot += 8; _slot += 1;

                qInfo() << "_ROUTE IS " + QString::number(_route) + " AND _SLOT IS " + QString::number(_slot);

                if(currentTile->paths.count(_slot) == 1)
                {
                    qInfo() << "FOUND PATH WITH SLOT";
                    currentTile->paths[_slot] = color + currentTile->paths[_slot];
                }
                else if(currentTile->paths.count(_route) == 1)
                {
                    qInfo() << "FOUND PATH WITH ROUTE";
                    currentTile->paths[_route] = color + currentTile->paths[_route];
                }

                currentTile->display();

                //CHECK IF PLAYER FELL OFF
                if(0 > players[p].row || 0 > players[p].column || 5 < players[p].row || 5 < players[p].column )
                {
                    players[p].isAlive = false;
                    break;
                }

                currentTile = tile[players[p].row][players[p].column];
            }
            while(!currentTile->pathCode.empty());

            drawPlayer(&players[p]);
        }
    }
}

void Tile::mousePressEvent(QMouseEvent *event)
{
    if(this->playable)

    {
        if(turn == this->playerIndex)
        {
            if(click1 == NULL)
            {
                click1 = this;
                //ON CHANGE OF click1
                click1->setStyleSheet("QLabel {background-color: rgb(170,95,127);}");
                QString qtileCode = QString::fromStdString(this->tileCode);
                selectedTile->setText(qtileCode);
            }
            else if(click1 != this)
            {
                click1->setStyleSheet("");
                click1 = this;
                //ON CHANGE OF click1
                click1->setStyleSheet("QLabel {background-color: rgb(170,95,127);}");
                QString qtileCode = QString::fromStdString(this->tileCode);
                selectedTile->setText(qtileCode);
            }
            else
            {
                qInfo() << "ROTATE";
                const QPixmap * pixmap = this->pixmap();
                QPixmap pix = *pixmap;
                QMatrix m;
                m.rotate(90);
                pix = pix.transformed(m);
                this->rotation = (this->rotation + 1)%4;
                //ON ROTATION CHANGE
                this->setPixmap(pix);
            }
         }
    }
    else
    {
        if(click1 != NULL)
        {
            int dy = this->row - players[turn].row;
            int dx = this->col - players[turn].column;

            if(dy == 0 && dx == 0)
            {
                this->playable = false;

                //TRANSFER TILE CODE
                this->tileCode = click1->tileCode;
                this->paths = click1->paths;
                std::string code = click1->tileCode;
                std::string codeCopy = click1->tileCode;
                qInfo() << "Processing tile code " + QString::fromStdString(code);
                for(int r = 0; r < click1->rotation; r++)
                {
                    for(int i = 0; i < codeCopy.length(); i++)
                    {
                        int x = codeCopy.at(i) - 1;
                        x = (x+2)%8 + 1;
                        int index = i;
                        index = (index+2)%8;
                        code[index] = '0' + x;
                    }
                    codeCopy = code;
                    qInfo() << "Rotation " + QString::number(r+1) + " -> " + QString::fromStdString(code);
                }
                this->pathCode = code;
                this->rotation = click1->rotation;

                movePlayers(this);

                int index = click1->playerIndex;
                //ON CHANGE OF click1

                //remove played tile
                players[turn].removeFromHand(click1->tileCode);

                //draw new tile
                bool newCard = deck->moreCard();

                std::string tile;
                if(newCard)
                {
                    tile = deck->draw();
                    players[turn].addTileToHand(tile);
                }


                qInfo() << "UPDATING HAND AFTER TILE HAS BEEN PLAYED";
                //refresh image of contents of hand
                GameManager::updateHand(&players[turn]);

                selectedTile->setText("None");
                click1->setStyleSheet("");
                click1 = NULL;

                //TURN CHANGE
                int endingturn = turn;
                do
                {
                    turn = (turn + 1)%players.size();
                    if(turn == endingturn) break;
                }
                while(!players[turn].isAlive);
            }
        }
    }
}

void Tile::construct()
{
    std::vector<int> v;

    for(int i = 0; i < this->tileCode.length(); i++)
    {
        if(std::find(v.begin(), v.end(), i+1) != v.end())
            continue;
        std::string path;
        int mod = i%2;
        if(mod != 0)
        {
            path += "2-";
        }

        int digit = this->tileCode[i] - '0';
        int pathnum = digit - (i/2)*2;
        std::string pathstr = std::to_string(pathnum);
        path += pathstr;
        v.push_back(digit);
        this->paths[i+1] = path;
    }
    qInfo() << "Tile constructed with " + QString::number(this->paths.size()) + " paths";
}

void Tile::display()
{   
    std::string tile = ":/RedTiles/a00000000.png";
    QString qtile = QString::fromStdString(tile);
    QPixmap tileimg = QPixmap(qtile);

    QPainter painter(&tileimg);

    std::map<int, std::string>::iterator p;
    for(p = this->paths.begin(); p != this->paths.end(); p++) {

        std::string path = ":/Paths/" + p->second + ".png";
        QPixmap pathimg = QPixmap(QString::fromStdString(path));

        int pathrot = (p->first-1)/2;
        //qInfo() << "Rendering path " + QString::fromStdString(path) + " rotated " + QString::number(pathrot) + " times for tile " + QString::fromStdString(this->tileCode);
        if(!pathimg.isNull())
        {
            QMatrix pm;
            pm.rotate(pathrot*90);
            pathimg = pathimg.transformed(pm);
            painter.drawPixmap(0,0,pathimg);
        }
        else
            qInfo() << "path error occured";
    }
    painter.end();

    QMatrix tm;
    tm.rotate(this->rotation*90);
    tileimg = tileimg.transformed(tm);

    QMatrix sm;
    sm.scale(0.5,0.5);
    tileimg = tileimg.transformed(sm);

    this->setPixmap(tileimg);
}

void validate(Tile *temp)//, int c)
{
    //temp->setPixmap(QPixmap(":/Tiles/a47618325.png"));
}

void Tile::tileDisplay()
{
    if(this->tileCode.length() > 0)
        this->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}:hover{background-color: rgb(170,85,127);}");
    else
        this->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}:hover{background-color: rgb(170,95,127);}");
}
