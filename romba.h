#ifndef ROMBA_H
#define ROMBA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Romba:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Romba(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    int getRombaX();
    int getRombaY();

private:
    QMediaPlayer * vacuumSound;
    QMediaPlayer * engineSound;

};
#endif // ROMBA_H
