#ifndef COUNTINGLABEL_H
#define COUNTINGLABEL_H

#include <QGraphicsTextItem>
#include <QFont>
#include <QString>

class CountingLabel: public QGraphicsTextItem
{
    Q_OBJECT
public:
    CountingLabel(QString l, int c, int x, int y);
public slots:
    void decreaseCounter();
private:
    QString label;
    int counter;
};

#endif // COUNTINGLABEL_H
