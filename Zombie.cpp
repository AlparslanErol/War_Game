#include "Zombie.h"

Zombie::Zombie(double xIn, double yIn, double speedIn, double damageIn, double hpIn, Manager* pIn, shared_ptr<Hero> pHeroIn, shared_ptr<Sprite> spIn)
{
    pGame = pIn;
    sprite = spIn;
    pHero = pHeroIn;

    x = xIn;
    y = yIn;
    speed = speedIn;
    damage = damageIn;
    hpmax = hpIn;
    hpcurrent = hpmax;
    attackCD = 0;
    attackrate = 2;
}

void Zombie::draw_Zombie()
{
    pGame->DrawSprite(x - 12, y - 12, sprite->zombieSprite, 1);
}

void Zombie::move_Zombie(float fElapsedTime)
{
    double dirX = pHero->getX() - x;
    double dirY = pHero->getY() - y;
    double dist = sqrt((dirX * dirX) + (dirY * dirY));
    x += dirX / dist * speed * fElapsedTime;
    y += dirY / dist * speed * fElapsedTime;
}

bool Zombie::is_Killed()
{
    if (hpcurrent <= 0)
    {
        return true;
    }
    return false;
}

void Zombie::zombie_Attack(float fElapsedTime)
{
    attackCD -= fElapsedTime;
    if ((pGame->distance(x, y, pHero->getX(), pHero->getY()) <= 8) && (attackCD <= 0))
    {
        pHero->setHpcurrent(pHero->getHpcurrent() - damage);
        attackCD = attackrate;
    }
}

void Zombie::DrawHPBar(int x, int y, int HPMax, int HPCurrent)
{
    double ratio = (double)(HPCurrent) / (double)HPMax;
    for (int i = x - 5; i < 5 + x; ++i)
        if (i < x - 5 + ratio * 10)
            pGame->DrawRect(i, y + 14, 1, 1, olc::GREEN);
        else
            pGame->DrawRect(i, y + 14, 1, 1, olc::RED);
}

double Zombie::getAttackCD()
{
    return attackCD;
}

double Zombie::getAttacrate()
{
    return attackrate;
}

int Zombie::getDamage()
{
    return damage;
}

void Zombie::setAttackCD(double _)
{
    attackCD = _;
}

void Zombie::setAttackrate(double _)
{
    attackrate = _;
}