
#include "Health.h"
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the health to 10
    health = 10;

    // draw the text
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 5
    setDefaultTextColor(Qt::white);
    setFont(QFont("Helvetica",15));
}

void Health::decrease(){
    health--;
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 4
}

int Health::getHealth(){
    return health;
}

void Health::setHealth(int health)
{
    this->health = health;
}
