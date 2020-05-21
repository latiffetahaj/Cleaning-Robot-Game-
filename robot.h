#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Robot: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    enum orientation_type
    {
        north,
        south,
        east,
        west
    };
    orientation_type currentOrientation = east;
    QMediaPlayer *vaccumSound;
    QMediaPlayer *robotSound;

public:
    Robot(QGraphicsItem *parent = 0);
    void setOrientation(orientation_type orientation);
        bool forward();
        void turnCW();
        void turnAntiCW();
        bool eastEnd();
        bool westEnd();
        bool northEnd();
        bool southEnd();
        bool zig();
        bool zag();
        void move();
        int getRobotX();
        int getRobotY();


public slots:
    void vacuum();


};


#endif // ROBOT_H
