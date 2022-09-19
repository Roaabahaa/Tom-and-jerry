#include "item.h"

Item::Item(QString imagePath, int r, int c)
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

    // set position
    setPosition(row, col);

}

void Item::setPosition(int r, int c)
{
    row = r;
    col = c;
    setPos(50 + (col * 50), (row* 50));
}
