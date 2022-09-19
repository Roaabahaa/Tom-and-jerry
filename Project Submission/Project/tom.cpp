#include "tom.h"

Tom::Tom(int** boardData, int level, int index): Character("tom.png", boardData, 14, 8)
{
    id = index;
    switch(id)
    {
    case 1: setPosition(1,8);break;
    case 2: setPosition(8,14);break;
    case 3: setPosition(8,1);break;
    }

    switch(level)
    {
    case 0: time = 400;break;
    case 1: time = 300;break;
    case 2: time = 200;break;
    }

    pathIndex = 0;
    map = new Map(boardData);
    switch(index)
    {
    case 0: path = map->calculateShortestPath(getData(), 67);break;
    case 1: path = map->calculateShortestPath(getData(), 47);break;
    case 2: path = map->calculateShortestPath(getData(), 58);break;
    case 3: path = map->calculateShortestPath(getData(), 74);break;
    }
}

void Tom::returnHome()
{
    switch(id)
    {
    case 0: setPosition(14,8);break;
    case 1: setPosition(1,8);break;
    case 2: setPosition(8,14);break;
    case 3: setPosition(8,1);break;
    }
}

void Tom::startMovement()
{
    // set timer to call the move function/slot every 200 seconds
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()), this, SLOT(move()));
    timer->start(time);
}

void Tom::stopMovement()
{
    // stop timer to stop calling of the move function
    timer->stop();
}

void Tom::move()
{
    int newRow, newCol;
    if(pathIndex<path.size())
    {
        getPosition(path.at(pathIndex), newRow, newCol);
        if(newRow>row)
        {
            moveDown();
        } else if(newRow<row) {
            moveUp();
        } else if(newCol>col) {
            moveRight();
        } else if(newCol<col) {
            moveLeft();
        }
        setPosition(row, col);
        pathIndex++;
    }
    // check for colliding items
    QList<QGraphicsItem *> colliding = collidingItems();
    for(QList<QGraphicsItem*>::iterator i = colliding.begin(); i!=colliding.end(); i++)
    {
        if(typeid(**i)==typeid(Jerry))
        {
            // catch jerry
            Jerry* jerry = qgraphicsitem_cast<Jerry*>(*i);
            jerry->catchMe();
        }
    }
}

void Tom::changeTarget()
{
    Jerry* jerry = static_cast<Jerry*>(sender());
    path = map->calculateShortestPath(this->getData(), jerry->getData());
    pathIndex = 0;
}

bool Tom::validMovement(movements movement)
{
    //row>=7 && row<=8 && col>=7 && col<=8
    if((movement == up && getData(row-1, col) >= 0)
            || (movement == down && getData(row+1, col) >= 0)
            || (movement == right && getData(row, col+1) >= 0)
            || ((movement == left && getData(row, col-1) >= 0)) )
            return true;

    return false;

}
