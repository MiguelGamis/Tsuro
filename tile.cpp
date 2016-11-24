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

void movePlayers(Tile * t)
{
    for(int p = 0; p < players.size(); p++)
    {
        if(players[p].row == t->row && players[p].column == t->col)
        {
            Tile * currentTile = t;

            do
            {
                int slot = players[p].slot;
                char x = currentTile->pathCode.at(slot-1);
                int route = x - '0';
                //qInfo() << QString::number(slot) + "th of " + QString::fromStdString(currentTile->pathCode) + " = " + QString::number(route);

                switch(route)
                {
                    case 1:
                        //qInfo() << "UP to slot 6...";
                        players[p].slot = 6;
                        players[p].row--;
                        break;
                    case 2:
                        //qInfo() << "UP to slot 5...";
                        players[p].slot = 5;
                        players[p].row--;
                        break;
                    case 3:
                        //qInfo() << "> to slot 8";
                        players[p].slot = 8;
                        players[p].column++;
                        break;
                    case 4:
                        //qInfo() << "> to slot 7...";
                        players[p].slot = 7;
                        players[p].column++;
                        break;
                    case 5:
                        //qInfo() << "DOWN to slot 2...";
                        players[p].slot = 2;
                        players[p].row++;
                        break;
                    case 6:
                        //qInfo() << "DOWN to slot 1...";
                        players[p].slot = 1;
                        players[p].row++;
                        break;
                    case 7:
                        //qInfo() << "< to slot 4...";
                        players[p].slot = 4;
                        players[p].column--;
                        break;
                    case 8:
                        //qInfo() << "< to slot 3...";
                        players[p].slot = 3;
                        players[p].column--;
                        break;
                }

//                qInfo() << "Player at (" + QString::number(players[p].row) + ", " + QString::number(players[p].column) + ")";

//                char color;
//                switch(p)
//                {
//                    case 0:
//                        color = 'b';
//                        break;
//                    case 1:
//                        color = 'r';
//                        break;
//                }

//                int jump = route - slot;
//                int pathrot;
//                qInfo() << "Jump is " + QString::number(jump);
//                qInfo() << "Route is " + QString::number(route);

//                std::string path = ":/Paths/"; path += color;

//                //FIND CORRECT PATH
//                if(jump > 0)
//                switch(jump)
//                {
//                    case 1:
//                    case 7:
//                        if(route%2 == 0)
//                        {
//                            path += "1.png";
//                            pathrot = ((route-jump)/2)*90;
//                        }
//                        else
//                        {
//                            path += "8.png";
//                            pathrot = ((route-jump)/2)*90;
//                        }
//                        break;
//                    case 2:
//                    case 6:
//                        if(route%2 == 0)
//                        {
//                            path += "3.png";
//                            pathrot = ((route-jump)/2)*90;
//                        }
//                        else
//                        {
//                            path += "2-4.png";
//                            pathrot = ((route-jump)/2)*90;
//                        }
//                        break;
//                    case 3:
//                        if(route%2 == 0)
//                        {
//                            path += "4.png";
//                            pathrot = ((route-jump)/2)*90;
//                        }
//                        else
//                        {
//                            path += "2-5.png";
//                            pathrot = ((route-jump)/2)*90;
//                        }
//                        break;
//                    case 4:
//                        if(route%2 == 0)
//                        {
//                            path += "2-6.png";
//                            pathrot = ((route-jump)/2)*90;
//                        }
//                        else
//                        {
//                            path += "5.png";
//                            pathrot = ((route-jump)/2)*90;
//                        }
//                        break;
//                    case 5:
//                        if(route%2 == 0)
//                        {
//                            path += "6.png";
//                            pathrot = ((route-jump)/2)*90;
//                        }
//                        else
//                        {
//                            path += "2-7.png";
//                            pathrot = ((route-jump)/2)*90;
//                        }
//                        break;
//                }
//                else
//                switch(jump)
//                {
//                    case -1:
//                    case -7:
//                        if(route%2 == 0)
//                        {
//                            path += "8.png";
//                            pathrot = (route/2)*90;
//                        }
//                        else
//                        {
//                            path += "1.png";
//                            pathrot = (route/2)*90;
//                        }
//                        break;
//                    case -2:
//                    case -6:
//                        if(route%2 == 0)
//                        {
//                            path += "2-4.png";
//                            pathrot = (route/2)*90;
//                        }
//                        else
//                        {
//                            path += "3.png";
//                            pathrot = (route/2)*90;
//                        }
//                        break;
//                    case -3:
//                        if(route%2 == 0)
//                        {
//                            path += "2-5.png";
//                            pathrot = (route/2)*90;
//                        }
//                        else
//                        {
//                            path += "4.png";
//                            pathrot = (route/2)*90;
//                        }
//                        break;
//                    case -4:
//                        if(route%2 == 0)
//                        {
//                            path += "5.png";
//                            pathrot = (route/2)*90;
//                        }
//                        else
//                        {
//                            path += "2-6.png";
//                            pathrot = (route/2)*90;
//                        }
//                        break;
//                    case -5:
//                        if(route%2 == 0)
//                        {
//                            path += "2-7.png";
//                            pathrot = (route/2)*90;
//                        }
//                        else
//                        {
//                            path += "6.png";
//                            pathrot = (route/2)*90;
//                        }
//                        break;
//                }

//                QString qpath = QString::fromStdString(path);
//                QPixmap pathimg = QPixmap(qpath);

//                QMatrix rm;
//                rm.rotate(pathrot);
//                rm.scale(0.5, 0.5);
//                pathimg = pathimg.transformed(rm);

//                if(!pathimg.isNull())
//                {
//                    const QPixmap * pixmap = currentTile->pixmap();
//                    QPixmap pix = *pixmap;
//                    QPainter painter(&pix);
//                    painter.drawPixmap(0, 0, pathimg);

//                    currentTile->setPixmap(pix);
//                }

                //check if player fell off
                if(0 > players[p].row || 0 > players[p].column || 5 < players[p].row || 5 < players[p].column )
                {
                    players[p].isAlive = false;
                    QMessageBox::information(myWidget, "Tsuro", "Game Over");
                    break;
                }

                currentTile = tile[players[p].row][players[p].column];
            }
            while(!currentTile->pathCode.empty());

            int deltax = 0;
            int deltay = 0;

            switch(players[p].slot)
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

            int x_ = 345 + (players[p].column*64) + deltax;
            int y_ = 120 + (players[p].row*64) + deltay;
            players[p].piece->setGeometry(x_, y_, 10, 10);
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

            this->playable = false;

            //TRANSFER TILE CODE
            this->tileCode = click1->tileCode;
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

            //TRANSFER IMAGE
            const QPixmap * pixmap = click1->pixmap();
            QPixmap pix = *pixmap;
            this->setPixmap(pix);

            movePlayers(this);

            int index = click1->playerIndex;
            //ON CHANGE OF click1

            //remove from hand
//            for( std::vector<std::string>::iterator iter = players[index].hand.begin(); iter != players[index].hand.end(); ++iter )
//            {
//                if( *iter == this->tileCode )
//                {
//                    players[index].hand.erase( iter );
//                    break;
//                }
//            }

            players[index].hand.pop_back();

            //draw new tile
            bool newCard = deck->moreCard();

            std::string tile;
            if(newCard)
            {
                tile = deck->draw();
                players[index].hand.push_back(tile);
            }

            //refresh image of contents of hand
            if(newCard)
            {
                click1->tileCode = tile;
                click1->rotation = 0;
                click1->playable = true;
                click1->display();
            }
            else
            {
                QPixmap m_pixmap;
                click1->setPixmap(m_pixmap);
                click1->playable = false;
//                delete click1;
            }

            selectedTile->setText("None");
            click1->setStyleSheet("");
            click1 = NULL;

            do
                turn = (turn + 1)%players.size();
            while(!players[turn].isAlive);
        }
    }
}

void Tile::display()
{
    std::string path = ":/RedTiles/a00000000.png";
    QString qpath = QString::fromStdString(path);
    QPixmap img = QPixmap(qpath);
    QMatrix rm;
    rm.scale(0.5, 0.5);
    img = img.transformed(rm);

//    QMatrix rm;
//    rm.rotate(this->rotation*90);
//    rm.scale(0.5, 0.5);
//    img = img.transformed(rm);
//    this->setPixmap(img);

    QPainter painter(&img);
//    painter.setBrush(Qt::NoBrush);
//    painter.setPen(Qt::red);
//    painter.drawRect(0,0,64,64);
    std::vector<int> v;

    for(int i = 0; i < this->tileCode.length(); i++)
    {
        if(std::find(v.begin(), v.end(), i+1) != v.end())
            continue;
        std::string path = ":/Paths/";
        int mod = i%2;
        if(mod != 0)
        {
            path += "2-";
        }

        int digit = this->tileCode[i] - '0';
        int relpath = digit - (i/2)*2;
        int rot = i/2;
        path += std::to_string(relpath);
        v.push_back(digit);

        path += ".png";
        QPixmap pathimg = QPixmap(QString::fromStdString(path));
        qInfo() << "Rendering path " + QString::number(i) + " with " + QString::fromStdString(path) + " rotated " + QString::number(rot) + " times for tile " + QString::fromStdString(this->tileCode);
        if(!pathimg.isNull())
        {
            QMatrix qm;
            qm.scale(0.5, 0.5);
            qm.rotate(rot*90);
            pathimg = pathimg.transformed(qm);
            painter.drawPixmap(0,0,pathimg);
        }
        else
            qInfo() << "path error occured";
    }

    this->setPixmap(img);
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
