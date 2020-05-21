#include "Dirt.h"
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <QDateTime>
#include <time.h>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"
#include <QRandomGenerator>

Dirt::Dirt(QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent)
{
    //srand((unsigned) time(0));
    //set random position for the dirt

    x1 = qrand() % 1150;
    y1 = rand() % 950;
    x2 = rand() % 1100;
    y2 = rand() & 900;

    if(x1 != x2)
    {
        setPos(x1,y2);
    }
    else
    {
        setPos(x2,y1);

    }


    //draw the dirt into the screen
    setPixmap(QPixmap(":/images/garbage1.png"));

}
