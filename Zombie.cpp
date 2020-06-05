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
    attackrate = 4;
    bonuses = vector<shared_ptr<Hp_Kit>>();
}

Zombie::Zombie()
{

}

double Zombie::distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool Zombie::is_Killed()
{
    if (hpcurrent <= 0)
    {
        return true;
    }
    return false;
}

void Zombie::hpCurrent()
{
    hpcurrent -= 1;
}