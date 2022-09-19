#include "gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(int level, int toms , User &account)
{
    // set up screen
    setFixedSize(810, 810);
    setWindowTitle("Tom and Jerry");

    scene = new QGraphicsScene;
    currentUser = account;

    // input data from board file
    data = new int*[16];
    for(int i=0; i<16; i++)
        *(data+i) = new int[16];
    QDir::setCurrent("C:/Users/moham/Desktop/Fall 2021/CS2/GameImages");
    QFile file("map.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString temp;

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            stream >> temp;
            *(*(data+i)+j) = temp.toInt();
        }
    }
    // set transforms for use in rotations
    QTransform rotate90, rotate180, rotate270;
    rotate90.rotate(90);
    rotate180.rotate(180);
    rotate270.rotate(270);

    // set images of different parts of the board
    QPixmap boardImages[5] = {QPixmap("solidBorder.jpg"), QPixmap("horizontalBorder.jpg"), QPixmap("tCornerBorder.jpg"), QPixmap("edgeCornerBorder.jpg"), QPixmap("blackBackground.jpg")};
    // scale images to correct dimensions
    for(int i=0; i<5; i++)
        boardImages[i] = boardImages[i].scaled(50,50);

    // add background images to board
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {    QGraphicsPixmapItem* temp = new QGraphicsPixmapItem();

            switch(*(*(data+i)+j))
            {
            case -1: temp->setPixmap(boardImages[0]); break;
            case -2: temp->setPixmap(boardImages[1]); break;
            case -3: temp->setPixmap(boardImages[1].transformed(rotate90)); break;
            case -4: temp->setPixmap(boardImages[2].transformed(rotate90)); break;
            case -5: temp->setPixmap(boardImages[2].transformed(rotate270)); break;
            case -6: temp->setPixmap(boardImages[2]); break;
            case -7: temp->setPixmap(boardImages[2].transformed(rotate180)); break;
            case -8: temp->setPixmap(boardImages[3]); break;
            case -9: temp->setPixmap(boardImages[3].transformed(rotate90)); break;
            case -10: temp->setPixmap(boardImages[3].transformed(rotate180)); break;
            case -11: temp->setPixmap(boardImages[3].transformed(rotate270)); break;
            case -20: temp->setPixmap(boardImages[4]); break;
            default: temp->setPixmap(boardImages[4]); break;
            }

            temp->setPos(50 + (50*j), (50*i));
            scene->addItem(temp);
        }
    }


    // create characters
    tomCounter = toms;
    tom = new Tom*[tomCounter];
    for(int i =0; i<tomCounter; i++)
    {
        *(tom+i) = new Tom(data, level, i);
        scene->addItem(*(tom+i));
    }
    jerry = new Jerry(data);

    // put focus on Jerry
    jerry->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    jerry->setFocus();

    // put jerry on top of all other items
    jerry->setZValue(1);

    // create power ups
    powerUps[0] = new PowerUp(5,5);
    powerUps[1] = new PowerUp(10,10);

    // create cheese
    cheeses[0] = new CheeseItem(1,1);
    cheeses[1] = new CheeseItem(14,14);
    cheeses[2] = new CheeseItem(1,14);
    cheeses[3] = new CheeseItem(14,1);

    // create labels
    HealthLabel = new CountingLabel("Lifes: ", 3, 500, 0);
    CheeseLabel = new CountingLabel("Cheese Left: ", 4, 300, 0);

    // add objects to scene
    scene->addItem(jerry);
    scene->addItem(powerUps[0]);
    scene->addItem(powerUps[1]);
    scene->addItem(cheeses[0]);
    scene->addItem(cheeses[1]);
    scene->addItem(cheeses[2]);
    scene->addItem(cheeses[3]);
    scene->addItem(HealthLabel);
    scene->addItem(CheeseLabel);

    // connect signals and slots
    // label counter slots
    connect(jerry, SIGNAL(decreaseHealthCounter()), HealthLabel, SLOT(decreaseCounter()));
    connect(jerry, SIGNAL(decreaseCheeseCounter()), CheeseLabel, SLOT(decreaseCounter()));
    // jerry motion change slots
    for(int i =0; i<tomCounter; i++)
    {
        connect(jerry, SIGNAL(changeMotion()), (*(tom+i)), SLOT(changeTarget()));
    }
    // game state change slots
    connect(jerry, SIGNAL(endGame()), this, SLOT(gameOver()));
    connect(jerry, SIGNAL(winGame()), this, SLOT(win()));

    for(int i =0; i<tomCounter; i++)
    {
        (*(tom+i))->startMovement();
    }
    setScene(scene);
    gameTimer.start();
}

void GameScreen::gameOver()
{
    for(int i =0; i<tomCounter; i++)
    {
        (*(tom+i))->stopMovement();
    }
    GameFinishScreen* screen = new GameFinishScreen(false);
    screen->show();
    hide();
}

void GameScreen::win()
{
    currentUser.setTime(gameTimer.elapsed());
    LeaderBoard::addUser(currentUser);
    GameFinishScreen* screen = new GameFinishScreen(true);
    screen->show();
    hide();
}


