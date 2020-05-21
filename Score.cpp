
#include "Score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    score = 0;

    // draw the text
    setPlainText(QString("Garbage: ") + QString::number(score)); // Score: 0

    setDefaultTextColor(Qt::black);
    setFont(QFont("Helvetica",15));
}

void Score::increase(){
    score++;
    setPlainText(QString("Garbage: ") + QString::number(score)); // Score: 1
}

int Score::getScore(){
    return score;
}

void Score::setScore(int score)
{
    this->score = score;
}
