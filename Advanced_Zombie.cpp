#include "Advanced_Zombie.h"

Advanced_Zombie::Advanced_Zombie(double xIn, double yIn, double speedIn, double damageIn, double hpIn, Manager* pIn, shared_ptr<Hero> pHeroIn, shared_ptr<Sprite> spIn)
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
    attackrate = 4;
    bonuses_1 = vector<shared_ptr<Shield>>();
}

void Advanced_Zombie::draw_Zombie()
{
    pGame->DrawSprite(x - 12, y - 12, sprite->zombieSprite_1, 1);
}

void Advanced_Zombie::createBonus(shared_ptr<Advanced_Zombie> object)
{
    bonuses_1.push_back(make_shared<Shield>(object->x, object->y, pGame, sprite, pHero));
}

void Advanced_Zombie::DrawHPBar()
{
    double ratio = (double)(hpcurrent) / (double)hpmax;
    for (int i = x - 5; i < 5 + x; ++i)
        if (i < x - 5 + ratio * 10)
            pGame->DrawRect(i, y + 14, 1, 1, olc::GREEN);
        else
            pGame->DrawRect(i, y + 14, 1, 1, olc::RED);
}

void Advanced_Zombie::zombie_Attack(float fElapsedTime)
{
    attackCD -= fElapsedTime;
    if (pHero->isCollide(x, y) && (attackCD <= 0))
    {
        pHero->hpCurrent(damage);
        attackCD = attackrate;
    }
}

bool Advanced_Zombie::isHit(int i)
{
    double a = x;
    double b = y;
    if (pHero->bullets[i]->isCollide(a, b))
    {
        return true;
    }
    return false;
}

void Advanced_Zombie::move_Zombie(float fElapsedTime)
{
    pHero->attractZombie(&x, &y, speed, fElapsedTime);
}