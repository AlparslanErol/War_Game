#pragma once
#include "Human.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;

class Human;
class Manager;
class Sprite;
class Hero;

class Zombie : public Human {

private:
    int damage;
    double attackCD;
    double attackrate;

    Manager* pGame;
    shared_ptr<Hero> pHero;
    shared_ptr<Sprite> sprite;

public:
    Zombie(double xIn, double yIn, double speedIn, double damageIn, double hpIn, Manager* pIn, shared_ptr<Hero> pHeroIn, shared_ptr<Sprite> spIn);

    void draw_Zombie();
    void move_Zombie(float fElapsedTime);
    bool is_Killed();
    void zombie_Attack(float fElapsedTime);
    void DrawHPBar(int x, int y, int HPMax, int HPCurrent);

    double getAttackCD();
    double getAttacrate();
    int getDamage();

    void setAttackCD(double _);
    void setAttackrate(double _);
};