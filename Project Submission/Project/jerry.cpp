#include "jerry.h"

Jerry::Jerry(int** boardData): Character("jerryNormal.png",boardData,7,7)
{
    // initalize variables
    lifes = 3;
    countCollectedCheese = 0;
    poweredUp = false;
    carryingCheese = false;
    carriedCheese = NULL;
}

void Jerry::catchMe()
{
    // first check that Jerry is not powered up
    if(!poweredUp)
    {
        // decrement lifes
        lifes--;

        // decrement label counter
        emit decreaseHealthCounter();

        // check if game is over
        if(lifes == 0)
        {
            emit endGame();
            return;
        }

        // check if Jerry is carrying cheese
        if(hasCheese())
            dropCheese();

        // return both Jerry and Tom to starting positions
        // return Tom home
        QList<QGraphicsItem *> colliding = collidingItems();
        // locate Tom's object
        for(QList<QGraphicsItem*>::iterator i = colliding.begin(); i!=colliding.end(); i++)
        {
            if(typeid(**i) == typeid(Tom))
            {
               Tom* tom = qgraphicsitem_cast<Tom*>(*i);
               tom->returnHome();
            }
        }
        //return Jerry home
        returnHome();
    }
}

void Jerry::powerUp()
{
    // update state
    poweredUp = true;

    // update Jerry's avatar
    // check if carrying cheese or not
    if(hasCheese())
        updateImage("jerryStrongCheese.png");
    else
        updateImage("jerryStrong.png");
}

void Jerry::powerDown()
{
    // update state
    poweredUp = false;

    //update Jerry's avatar
    if(hasCheese())
        updateImage("jerryNormalCheese.png");
    else
        updateImage("jerryNormal.png");
}

bool Jerry::hasPowerUp()
{
    return poweredUp;
}

bool Jerry::hasCheese()
{
    return carryingCheese;
}

void Jerry::carryCheese(CheeseItem* cheese)
{
    // first check if not already carrying cheese
    if(!hasCheese())
    {
        carryingCheese = true;
        // store cheese
        carriedCheese = cheese;
        // remove cheese from scene
        scene()->removeItem(carriedCheese);

        // update Jerry's avatar
        // check if Jerry has a power up or not
        if(hasPowerUp())
            updateImage("jerryStrongCheese.png");
        else
            updateImage("jerryNormalCheese.png");
    }
}

void Jerry::dropCheese()
{
    // first check if you already are carrying cheese
    if(hasCheese())
    {
        // re-add cheese back to scene
        scene()->addItem(carriedCheese);
        // remove carried cheese
        carriedCheese = NULL;
        carryingCheese = false;
        // change Jerry's avater to without cheese
        if(hasPowerUp())
            updateImage("jerryStrong.png");
        else
            updateImage("jerryNormal.png");
    }
}

void Jerry::reachedHome()
{
    // check if carrying cheese to collect it succesfully
    if(hasCheese())
    {
        // increment number of cheese collected
        countCollectedCheese++;

        switch(countCollectedCheese)
        {
        case 1: carriedCheese->setPosition(7, 7); break;
        case 2: carriedCheese->setPosition(7, 8); break;
        case 3: carriedCheese->setPosition(8, 7); break;
        case 4: carriedCheese->setPosition(8, 8); break;
        }

        // add updated position cheese to scene
        scene()->addItem(carriedCheese);

        // update counting label
        emit decreaseCheeseCounter();

        // empty carriedCheese
        carriedCheese = NULL;

        carryingCheese = false;

        if(hasPowerUp())
            updateImage("jerryStrong.png");
        else
            updateImage("jerryNormal.png");

        // check if collected all 4 cheese
        if(countCollectedCheese == 4)
            emit winGame();
    }
}

void Jerry::keyPressEvent(QKeyEvent* event)
{
    // move player according to key press if valid movement is supplied
    if(event->key() == Qt::Key_Up && validMovement(up))
    {
        moveUp();
        emit changeMotion();
    }
    else if(event->key() == Qt::Key_Down && validMovement(down))
    {
        moveDown();
        emit changeMotion();
    }
    else if(event->key() == Qt::Key_Right && validMovement(right))
    {
        moveRight();
        emit changeMotion();
    }
    else if(event->key() == Qt::Key_Left && validMovement(left))
    {
        moveLeft();
        emit changeMotion();
    }

    // check if Jerry reached home
    if(atHome())
        reachedHome();

    // check for colliding items
    QList<QGraphicsItem *> colliding = collidingItems();
    for(QList<QGraphicsItem*>::iterator i = colliding.begin(); i!=colliding.end(); i++)
    {
        // check if colliding with Power Up item
        if(typeid(**i)==typeid(PowerUp))
        {
            // remove Power Up from scene
            scene()->removeItem(*i);
            // power up jerry
            powerUp();
            // set a timer to remove power up effect after 10 seconds
            QTimer::singleShot(10000, this, SLOT(powerDown()));
        }

        // check if colliding with Cheese item
        else if(typeid(**i) == typeid(CheeseItem))
        {
            // make sure jerry is not taking cheese stored at home
            if(!atHome())
                carryCheese(qgraphicsitem_cast<CheeseItem*>(*i));
        }

        // check if colliding with Tom
        else if(typeid(**i) == typeid(Tom))
        {
            catchMe();
        }
    }
}

void Jerry::returnHome()
{
    setPosition(7,7);
    emit changeMotion();
}

bool Jerry::atHome()
{
    return (row>=7 && row<=8 && col>=7 && col<=8);
}

bool Jerry::validMovement(movements movement)
{
    if((movement == up && (getData(row-1, col) >= 0 || getData(row-1, col) == -20))
                || (movement == down && (getData(row+1, col) >= 0 || getData(row+1, col) == -20))
                || (movement == right && (getData(row, col+1) >= 0|| getData(row, col+1) == -20))
                || (movement == left && (getData(row, col-1) >= 0 || getData(row, col-1) == -20)))
                return true;

        return false;

}
