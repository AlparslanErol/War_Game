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

bool Bullet::isCollide(double xIn, double yIn)
{
    if (distance(x, y, xIn, yIn) < 10)
    {
        return true;
    }
    return false;
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

bool Bullet::erase()
{
    if (x < 0 || x > pGame->ScreenWidth() || y < 0 || y > pGame->ScreenHeight())
    {
        return true;
    }
    return false;
}

double Bullet::distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}