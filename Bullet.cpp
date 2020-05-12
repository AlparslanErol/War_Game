#include "Bullet.h"

Bullet::Bullet(double xIn, double yIn, double dirXIn, double dirYIn, double speedIn, double damageIn, Manager* pIn)
{
    pGame = pIn;

    x = xIn;
    y = yIn;
    dirX = dirXIn;
    dirY = dirYIn;
    speed = speedIn;
    damage = damageIn;
}

void Bullet::draw_Bullet()
{
    pGame->DrawCircle(x, y, 1, olc::YELLOW);
}

void Bullet::bullet_move(float fElapsedTime)
{
    x += dirX * speed * fElapsedTime;
    y += dirY * speed * fElapsedTime;
}
double Bullet::getX()
{
    return x;
}
double Bullet::getY()
{
    return y;
}
double Bullet::getDamage()
{
    return damage;
}
double Bullet::get_dirX()
{
    return dirX;
}
double Bullet::get_dirY()
{
    return dirY;
}

double Bullet::getSpeed()
{
    return speed;
}

void Bullet::setX(double _)
{
    x = _;
}

void Bullet::setY(double _)
{
    y = _;
}