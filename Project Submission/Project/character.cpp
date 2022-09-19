#include "character.h"

Character::Character(QString imagePath, int** boardData, int r, int c)
{
    // create Pixmap with supplied imagePath
    QPixmap image(imagePath);
    // scale image to correct dimensions
    image = image.scaled(50,50);
    // set Pixmap to the QObject
    setPixmap(image);

    // initalize row and column
    row = r;
    col = c;

    // set direction to 1 since initaly the object will look to the right
    direction = 1;

    // set the position of the QObject in the board
    setPosition(row, col);

    // initalize 2D data array
    data = new int*[16];
    for(int i=0; i<16; i++)
        *(data+i) = new int[16];

    // copy data from supplied boardData 2D array into the data array
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            *(*(data+i)+j) = *(*(boardData+i)+j);
        }
    }

}

void Character::setDirection(int d)
{
    direction = d;
    QTransform transform;

    // check if object will look to the left
    if(d == -1)
    {
        // flip the object over the y-axis
        transform.scale(-1,1);
        transform.translate(-50,0);
    }

    // transfrom the QObject
    // if object is looking to the right an empty transfrom will be set making the object not transformed (return to original orientation
    setTransform(transform);
}

void Character::setPosition(int r, int c)
{
    // update row and col variables
    row = r;
    col = c;

    //update the position of the QObject
    setPos(50 + col*50, row*50);
}

void Character::updateImage(QString imagePath)
{
    // create Pixmap with supplied imagePath
    QPixmap temp(imagePath);
    // scale image to correct dimensions
    temp = temp.scaled(50,50);
    // set Pixmap to the QObject
    setPixmap(temp);
}

void Character::moveUp()
{
    // check if movement is valid
    if(validMovement(up))
        setPosition(row-1,col);
}
void Character::moveDown()
{
    // check if movement is valid
    if(validMovement(down))
        setPosition(row+1,col);
}

void Character::moveRight()
{
    // check if movement is valid
    if(validMovement(right))
    {
        // make character look to the right
        setDirection(1);
        setPosition(row,col+1);
    }
}

void Character::moveLeft()
{
    // check if movement is valid
    if(validMovement(left))
    {
        // make character look to the left
        setDirection(-1);
        setPosition(row,col-1);
    }
}

int Character::getData()
{
    return *(*(data+row)+col);
}
int Character::getData(int r, int c)
{
    return *(*(data+r)+c);
}

void Character::getPosition(int current, int& row, int& col)
{
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            if(*(*(data+i)+j) == current)
            {
                row = i;
                col = j;
                return;
            }
        }
    }
    row = -1;
    col = -1;
}

