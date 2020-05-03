#include "Bonus.h"

Bonus::Bonus(double xIn, double yIn, Hero *heroIn){
    x = xIn;
    y = yIn;
    hero = heroIn;
    bonuses = std::vector<Bonus>();
    bonusSprite = std::shared_ptr<olc::Sprite>();
    bonusSprite = make_shared<olc::Sprite>("Sprites/firstaid.png");
}

Bonus::~Bonus() {
}

bool Bonus::OnUserUpdate(float fElapsedTime) {
    
    //BONUS PICK UP
    for (int i = 0; i < bonuses.size(); i++)
    {
        if (distance(hero->getX(), hero->getY(), bonuses[i].x, bonuses[i].y) <= 10)
        {
            if (hero->getHpCurr() + 20 < hero->getHpMax())
            {
                hero->setHpCurr(hero->getHpCurr() + 20);
            }
            else
            {
                hero->setHpCurr(hero->getHpMax());
            }

            bonuses.erase(bonuses.begin() + i);
            i--;

        }

    }
    //BONUS PICK UP
    return true;
}

double Bonus::distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double Bonus::getX() {
    return x;
}
double Bonus::getY() {
    return y;
}
double Bonus::setX(double _) {
    return x = _;
}
double Bonus::setY(double _) {
    return y = _;
}