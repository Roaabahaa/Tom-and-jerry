#include "countinglabel.h"

CountingLabel::CountingLabel(QString l, int c, int x, int y)
{
    // personalize font
    QFont font;
    font.setBold(true);
    font.setPixelSize(20);
    setDefaultTextColor(Qt::white);
    setFont(font);

    // set position of TextItem
    setPos(x,y);

    // initalize counter starting value
    counter = c;

    // set label text
    label = l;

    // set TextItem text
    setPlainText(label + QString::number(counter));
}

void CountingLabel::decreaseCounter()
{
    // decrement counter
    counter--;

    // update label text
    setPlainText(label + QString::number(counter));
}
