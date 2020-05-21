#include "robot.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Game.h"
#include "Dirt.h"
#include "romba.h"

extern Game *game; // there is an external global object called game

Romba::Romba(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{

    //set the vacuum sound
    vacuumSound = new QMediaPlayer();
    vacuumSound->setMedia(QUrl("qrc:/sounds/vacuumSound1.wav"));

    //set the engine sound
    engineSound = new QMediaPlayer();
    engineSound->setMedia(QUrl("qrc:/sounds/rombaSound.wav"));

    //set graphic for the robot
    setPixmap(QPixmap(":/images/romba.png"));
}

void Romba::keyPressEvent(QKeyEvent *event)
{

    // get a list of all the items that robot is vacuuming
        QList<QGraphicsItem *> colliding_items = collidingItems();
        // if one of the colliding items is a Dirt, vacuum the dirt
            for (int i = 0, n = colliding_items.size(); i < n; ++i)
            {
                if (typeid(*(colliding_items[i])) == typeid(Dirt))
                {
                    game->rombaScore->increase();
                    //play the vaccum sound
                    if(vacuumSound->state() == QMediaPlayer::PlayingState)
                    {
                        vacuumSound->setPosition(0);
                    }
                    else if(vacuumSound->state() == QMediaPlayer::StoppedState)
                    {
                        vacuumSound->play();
                    }
                    // remove the dirt from the scene (still on the heap)
                    scene()->removeItem(colliding_items[i]);

                    // delete the dirt from the heap to save memory
                    delete colliding_items[i];

                    if((game->score->getScore() + game->rombaScore->getScore()) == 4)
                    {
                        game->gameOver();
                    }



                    // return (all code below refers to a non existint bullet)
                    return;

                }
                else if(typeid(*(colliding_items[i])) == typeid(Robot))
                {
                    if(pos().x() == game->robot->getRobotX() && pos().y() != game->robot->getRobotY() )
                    {
                        if(pos().y() < game->robot->getRobotY())
                        {
                            setPos(x(),y()+30);
                        }
                        else if(pos().y() > game->robot->getRobotY())
                        {
                            setPos(x(),y()-30);
                        }
                    }
                    else if(pos().x() != game->robot->getRobotX() && pos().y() == game->robot->getRobotY())
                    {
                        if(pos().x() < game->robot->getRobotX())
                        {
                            setPos(x()-30,y());
                        }
                        else if(pos().x() > game->robot->getRobotX())
                        {
                           setPos(x()+30,y());
                        }

                    }
                    else if(pos().x() != game->robot->getRobotX() && pos().y() != game->robot->getRobotY())
                    {
                        if(pos().x() < game->robot->getRobotX() && pos().y() > game->robot->getRobotY())
                        {
                            setPos(x()-20,y()+20);
                        }
                        else if(pos().x() < game->robot->getRobotX() && pos().y() < game->robot->getRobotY())
                        {
                            setPos(x()-20,y()-20);
                        }
                        else if(pos().x() > game->robot->getRobotX() && pos().y() < game->robot->getRobotY())
                        {
                            setPos(x()+20,y()-20);
                        }
                        else if(pos().x() > game->robot->getRobotX() && pos().y() > game->robot->getRobotY())
                        {
                            setPos(x()+20,y()+20);
                        }


                    }
                    game->health->decrease();
                    if(game->health->getHealth() == 0)
                    {
                        game->gameOver();
                    }

                }
            }
    // move the player left and right
    if (event->key() == Qt::Key_Left)
    {

        if (pos().x() > 0)
        {
           // engineSound->play();
           setPos(x()-10,y());

        }

    }
    else if (event->key() == Qt::Key_Right)
    {

        if (pos().x() < 1100)
        {
           // engineSound->play();
            setPos(x()+10,y());
        }

    }
    else if(event->key() == Qt::Key_Up)
    {

        if(pos().y() > 60)
        {
           // engineSound->play();
            setPos(x(),y()-10);
        }

    }
    else if(event->key() == Qt::Key_Down)
    {

        if(pos().y() < 900)
        {
           // engineSound->play();
            setPos(x(),y()+10);
        }
    }
}

int Romba::getRombaX()
{
    return pos().x();
}
int Romba::getRombaY()
{
    return pos().y();
}
