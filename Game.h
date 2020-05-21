#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QVector>
#include "robot.h"
#include "Dirt.h"
#include "Score.h"
#include "romba.h"
#include "Health.h"
#include <QFile>

class Game: public QGraphicsView
{
private:
    int random;
     void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    Robot *robot;
    Romba *romba;

    //create a vector of dirts
    QVector<Dirt*> dirts;

    Dirt *dirt;
    Dirt *dirt1;
    Dirt *dirt2;
    Dirt *dirt3;

    Score *score;
    Score *rombaScore;
    Health *health;

    void gameOver();
    void displayGameOverWindow(QString textToDisplay);
    void writeToFile(QString textToWrite);

};



#endif // GAME_H
