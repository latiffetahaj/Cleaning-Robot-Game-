#include "Game.h"
#include "Button.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QImage>
#include <QString>
#include <stdlib.h>
#include <QMessageBox>

#include <QDebug>



Game::Game(QWidget *parent)
{
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1200,1000); // make the scene 800x600 instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/images/floor.jpg")));

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200,1000);

    //create a file to save the score
    QFile file("myFile.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"title","file not open");

    }
    //initialize a random variable between 0-10
    /*
    random = rand() % 20;

    for(int i = 0; i<random;i++)
    {

        dirts.push_back(new Dirt());
        scene->addItem(dirts[i]);
    }
    */
    //create a dirt and add to the  scene
     dirt = new Dirt();
     scene->addItem(dirt);

     //create the score for first robot
     score = new Score();
     scene->addItem(score);

     dirt1 = new Dirt();
     scene->addItem(dirt1);

     //create the score for the romba robot
     rombaScore = new Score();
     rombaScore->setDefaultTextColor(Qt::darkRed);
     rombaScore->setPos(rombaScore->x()+930,rombaScore->y());
     rombaScore->setFont(QFont("Helvetica",15));
     scene->addItem(rombaScore);

     dirt2 = new Dirt();
     scene->addItem(dirt2);


     //create the health
     health = new Health();
     health->setPos(health->x()+500,health->y());
     scene->addItem(health);

    dirt3 = new Dirt();
    scene->addItem(dirt3);


    //create the robot in the scene
    robot = new Robot();
    robot->setPos(0,60);
    //make the robot focusable
    //robot->setFlag(QGraphicsItem::ItemIsFocusable);
     //robot->setFocus();
     // add the robot to the scene
     scene->addItem(robot);

     //add romba to the scene
    romba = new Romba();
    romba->setPos(1100,900);
    romba->setFlag(QGraphicsItem::ItemIsFocusable);
    romba->setFocus();
    scene->addItem(romba);








     show();



}

void Game::gameOver()
{
   robot->setVisible(false);
   romba->setVisible(false);
    QString message;
    //count
    if(health->getHealth() == 0)
    {
         message = "Robots have been destroyed!";
         writeToFile(message);
    }
    else if(rombaScore->getScore() > score->getScore())
    {
        message = "Red robot has won!";

        writeToFile( message + "\n" + QString("Red Robot score: ") + QString::number(rombaScore->getScore()));
    }
    else if(score->getScore() > rombaScore->getScore())
    {
        message = "Black robot has won!";

        writeToFile( message + "\n" + QString("Black Robot score: ") + QString::number(score->getScore()));
    }
    else
    {
        message = "Tie game!";
        writeToFile(message);
    }

    displayGameOverWindow(message);

}

void Game::displayGameOverWindow(QString textToDisplay)
{
    //disable all scene items
    for(size_t i = 0, n = scene->items().size(); i < n; i++)
    {
        scene->items()[i]->setEnabled(false);
    }
    //pop up semi transparent panel
    drawPanel(0,0,1200,1000,Qt::black,0.65);

    //draw panel
    drawPanel(400,300,400,400,Qt::lightGray,0.85);

 //quit button
 Button *quit = new Button(QString("Quit"));
 quit->setPos(500,575);
 scene->addItem(quit);

 connect(quit,SIGNAL(clicked()),this,SLOT(close()));
QGraphicsTextItem *overText = new QGraphicsTextItem(textToDisplay);
overText->setPos(430,350);
scene->addItem(overText);
}

void Game::writeToFile(QString textToWrite)
{
    //create a file to save the score

    try
    {
        QFile file("C:\\Users\\latif\\OneDrive - Borough of Manhattan Community College\\Desktop\\Spring 2020\\CSC 211H\\QT Projects\\romba\\myFile.txt");
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this,"title","file not open");
            throw QString("Could not open the file");

        }
        QTextStream out(&file);
        out << textToWrite << endl;
        file.flush();
        file.close();

    } catch (QString s)
    {

        drawPanel(400,300,400,100,Qt::lightGray,0.65);
        QGraphicsTextItem *displayMessage = new QGraphicsTextItem(s);
        displayMessage->setPos(420,320);
        scene->addItem(displayMessage);

    }

}



void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}
