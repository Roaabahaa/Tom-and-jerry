#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QElapsedTimer>
#include "tom.h"
#include "jerry.h"
#include "cheeseitem.h"
#include "powerup.h"
#include "countinglabel.h"
#include "gamefinishscreen.h"
#include "map.h"
#include "user.h"
#include "leaderboard.h"

class GameScreen: public QGraphicsView
{
    Q_OBJECT
public:
    GameScreen(int level, int toms, User &account);
    CountingLabel *HealthLabel, *CheeseLabel;
public slots:
    void gameOver();
    void win();
private:
    QElapsedTimer gameTimer;
    QGraphicsScene* scene;
    CheeseItem* cheeses[4];
    PowerUp* powerUps[2];
    int** data;
    int tomCounter;
    Tom** tom;
    Jerry* jerry;
    User currentUser;
};

#endif // GAMESCREEN_H
