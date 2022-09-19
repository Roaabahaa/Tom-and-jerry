#ifndef TOM_H
#define TOM_H

#include <QTimer>
#include <QList>
#include <QVector>
#include "character.h"
#include "jerry.h"
#include "map.h"
#include "time.h"
#include "stdlib.h"


class Tom: public Character
{
    Q_OBJECT
public:
    Tom(int** boardData, int level, int index);
    virtual void returnHome();
    void startMovement();
    void stopMovement();
    virtual bool validMovement(movements movement);
public slots:
    void move();
    void changeTarget();
private:
    Map* map;
    QVector<int> path;
    int pathIndex;
    int time, id;
    QTimer* timer;
};

#endif // TOM_H
