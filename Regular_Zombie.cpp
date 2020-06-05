#include "Regular_Zombie.h"

Regular_Zombie::Regular_Zombie(double xIn, double yIn, double speedIn, double damageIn, double hpIn, Manager* pIn, shared_ptr<Hero> pHeroIn, shared_ptr<Sprite> spIn)
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
    bonuses = vector<shared_ptr<Hp_Kit>>();
}

void Regular_Zombie::draw_Zombie()
{
    pGame->DrawSprite(x - 12, y - 12, sprite->zombieSprite, 1);
}

void Regular_Zombie::createBonus(shared_ptr<Regular_Zombie> object)
{
    bonuses.push_back(make_shared<Hp_Kit>(object->x, object->y, pGame, sprite, pHero));
}

void Regular_Zombie::DrawHPBar()
{
    double ratio = (double)(hpcurrent) / (double)hpmax;
    for (int i = x - 5; i < 5 + x; ++i)
        if (i < x - 5 + ratio * 10)
            pGame->DrawRect(i, y + 14, 1, 1, olc::GREEN);
        else
            pGame->DrawRect(i, y + 14, 1, 1, olc::RED);
}

void Regular_Zombie::zombie_Attack(float fElapsedTime)
{
    attackCD -= fElapsedTime;
    if (pHero->isCollide(x, y) && (attackCD <= 0))
    {
        pHero->hpCurrent(damage);
        attackCD = attackrate;
    }
}

bool Regular_Zombie::isHit(int i)
{
    if (pHero->bullets[i]->isCollide(x,y))
    {
        return true;
    }
    return false;
}

void Regular_Zombie::move_Zombie(float fElapsedTime)
{
    pHero->attractZombie(&x, &y, speed, fElapsedTime);
}