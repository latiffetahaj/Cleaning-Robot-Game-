#include <QApplication>
#include "Game.h"

//Latif Fetahaj
//CSC 211
//Honors Project
//ID: 23838210
//Thursday, May 21st 2020

//Credits: Abdullah Aghazadah for providing videos
//on youtube how to use the Qt IDE
//link to his channel
//https://www.youtube.com/channel/UClzV7jGJREjvCTzfGTrdrkQ




Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();


    return a.exec();
}
