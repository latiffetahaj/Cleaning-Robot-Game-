#include "robot.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMediaPlaylist>
#include "Game.h"
#include "Dirt.h"

extern Game *game; // there is an external global object called game

Robot::Robot(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    //set the vacuum sound
    vaccumSound = new QMediaPlayer();
    vaccumSound->setMedia(QUrl("qrc:/sounds/vacuumSound1.wav"));

    /*
    //play the engine sound in the background all the time
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/robotSound1.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    robotSound= new QMediaPlayer();
    robotSound->setPlaylist(playlist);
    robotSound->play();
*/
    //set graphic for the robot
    setPixmap(QPixmap(":/images/robot.png"));

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(vacuum()));

    //start the timer
    timer->start(50);

}
void Robot::setOrientation(orientation_type orientation)
{
    currentOrientation = orientation;
}

void Robot::turnCW()
{
    if (currentOrientation == east) // if the orientation is east, turn clockwise to south
    {
        setOrientation(south);
    }
    else if (currentOrientation == south) // if the orientation is south, turn clockwise to west
    {
        setOrientation(west);
    }
    else if (currentOrientation == west) // if the orientation is west, turn clockwise to north
    {
        setOrientation(north);
    }
    else if (currentOrientation == north) // if the orientation is north, turn clockwise to east
    {
        setOrientation(east);
    }
}
void Robot::turnAntiCW()
{
    if (currentOrientation == east) // if the orientation is east, turn anticlockwise to north
    {
        setOrientation(north);
    }
    else if (currentOrientation == north) // if the orientation is north, turn anticlockwise to west
    {
        setOrientation(west);
    }
    else if (currentOrientation == west) // if the orientation is west, turn anticlockwise to south
    {
        setOrientation(south);
    }
    else if (currentOrientation == south) // if the orientation is south, turn anticlockwise to east
    {
        setOrientation(east);
    }
}

bool Robot::eastEnd()
{

    if (pos().x() == 1100)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Robot::westEnd()
{
    if (pos().x() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Robot::northEnd()
{
    if (pos().y() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Robot::southEnd()
{
    if (pos().y() == 900)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Robot::forward()
{
    if(currentOrientation == east && pos().x() < 1100)
    {
        setPos(x()+10,y());

        return true;
    }
    else if(currentOrientation == south && pos().y() < 900)
    {
        setPos(x(),y()+10);

        return true;
    }
    else if(currentOrientation == north && pos().y() > 0)
    {
        setPos(x(),y()-10);

        return true;
    }
    else if(currentOrientation == west && pos().x() > 0)
    {
        setPos(x()-10,y());
        return true;
    }
    else
    {
        return false;
    }
}

bool Robot::zag()
{
    if (eastEnd()) // if the robot has reached the eastEnd
    {
        turnCW(); // turn clockwise
        forward();
        forward();
        forward();
        forward();
        turnCW(); // turn clockwise again, now facing west

        return true;
    }
    else
    {
        return false;
    }
}

void Robot::move()
{
    forward();
    if(eastEnd())
    {
        zag();

    }
    if(westEnd())
    {
        zig();

    }

}

int Robot::getRobotX()
{
    return pos().x();

}
int Robot::getRobotY()
{
    return pos().y();
}

bool Robot::zig()
{
    if (westEnd()) //if the robot has reached the westEnd
    {
        turnAntiCW(); // turn anti clockwise
        forward();
        forward();
        forward();
        forward();
        turnAntiCW(); // turn anti clockwise again, now facing east

        return true;
    }
    else
    {
        return false;
    }
}
void Robot::vacuum()
{
    // get a list of all the items that robot is vacuuming
        QList<QGraphicsItem *> colliding_items = collidingItems();

        // if one of the colliding items is a Dirt, vacuum the dirt
            for (int i = 0, n = colliding_items.size(); i < n; ++i)
            {
                if (typeid(*(colliding_items[i])) == typeid(Dirt))
                {
                    //play the vaccum sound
                    if(vaccumSound->state() == QMediaPlayer::PlayingState)
                    {
                        vaccumSound->setPosition(0);
                    }
                    else if(vaccumSound->state() == QMediaPlayer::StoppedState)
                    {
                        vaccumSound->play();
                    }

                    //increase the score
                    game->score->increase();

                    // remove the dirt from the scene (still on the heap)
                    scene()->removeItem(colliding_items[i]);



                    // delete the dirt from the heap to save memory
                    delete colliding_items[i];

                    if((game->score->getScore() + game->rombaScore->getScore()) == 4)
                    {
                        game->gameOver();
                    }



                    // return (all code below refers to
                    return;

                }

            }
             move();

}
