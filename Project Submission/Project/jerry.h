#ifndef JERRY_H
#define JERRY_H

#include <QKeyEvent>
#include <QGraphicsScene>
#include "character.h"
#include "powerup.h"
#include "cheeseitem.h"
#include "tom.h"

class Jerry: public Character
{
    Q_OBJECT
public:
    Jerry(int** boardData);
    void catchMe();
    void powerUp();
    void carryCheese(CheeseItem* cheese);
    void dropCheese();
    bool hasCheese();
    bool hasPowerUp();
    bool atHome();
    virtual bool validMovement(movements movement);
    virtual void returnHome();
    void reachedHome();
public slots:
    void powerDown();
    void keyPressEvent(QKeyEvent* event);
signals:
    void decreaseCheeseCounter();
    void decreaseHealthCounter();
    void endGame();
    void winGame();
    void changeMotion();
private:
    int lifes, countCollectedCheese;
    bool poweredUp, carryingCheese;
    CheeseItem* carriedCheese;
};

#endif // JERRY_H
