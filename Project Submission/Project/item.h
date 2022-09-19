#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>

class Item: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Item(QString imagePath, int r, int c);
    void setPosition(int r, int c);
private:
    int row, col;
};

#endif // ITEM_H
