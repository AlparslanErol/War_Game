#pragma once
#include "Manager.h"

class Bonus {

private:
    double x;
    double y;
    class Hero* hero;

public:
    Bonus(double xIn, double yIn, Hero *heroIn);
    ~Bonus();
    std::vector<class Bonus> bonuses;
    std::shared_ptr<olc::Sprite> bonusSprite;

    bool OnUserUpdate(float fElapsedTime); //override

    double getX();
    double setX(double _);

    double getY();
    double setY(double _);
    
    double distance(double x1, double y1, double x2, double y2);
};