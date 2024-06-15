#include "position.h"

Position::Position(int x, int y)
{
    this->x=x;
    this->y=y;
}

int Position::getXPos()
{
    return this->x;
}

int Position::getYPos()
{
 return this->y;
}

void Position::setXPos(int x)
{
 this->x=x;
}

void Position::setYPos(int y)
{
    this->y=y;
}

void Position::setPos(int x, int y)
{
    this->x=x;
    this->y=y;
}
