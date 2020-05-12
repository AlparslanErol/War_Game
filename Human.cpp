#include "Human.h"
#include <iostream>

Human::Human(){
}


double Human::getX()
{
    return x;
}

double Human::getY()
{
    return y;
}

double Human::getSpeed()
{
    return speed;
}

double Human::getHpmax()
{
    return hpmax;
}

double Human::getHpcurrent()
{
    return hpcurrent;
}

void Human::setX(double _)
{
    x = _;
}

void Human::setY(double _)
{
    y = _;
}

void Human::setSpeed(double _)
{
    speed = _;
}

void Human::setHpmax(double _)
{
    hpmax = _;
}

void Human::setHpcurrent(double _)
{
    hpcurrent = _;
}

void Human::DrawHPBar(int x, int y, int HPMax, int HPCurrent)
{
    cout << "asdasjdhaskdj";
}
