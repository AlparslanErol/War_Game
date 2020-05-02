#pragma once
#include "Manager.h"
using namespace std;

class Hero {

private:
    double x;
    double y;
    double heroSpeed;
    double hpmax;
    double hpcurr;


public:
    Hero();
    ~Hero();
    std::shared_ptr<olc::Sprite> manSprite;

    bool OnUserUpdate(float fElapsedTime); //override

    double getX();
    double setX(double _);
    double getY();
    double setY(double _);
    double getHeroSpeed();
    double setHeroSpeed(double _);
    double getHpMax();
    double setHpMax(double _);
    double getHpCurr();
    double setHpCurr(double _);
};
