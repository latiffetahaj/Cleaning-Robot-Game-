#ifndef DIRT_H
#define DIRT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Dirt: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Dirt(QGraphicsItem * parent=0);

public slots:
   // void random();

private:
    int x1;
    int y1;
    int x2;
    int y2;


};
#endif // DIRT_H
