#pragma once
#include "Human.h"
#include <vector>
#include <memory>
using namespace std;

class Human;
class Manager;
class Sprite;
class Hero;
class Bonus;
class Hp_Kit;
class Shield;


class Zombie : public Human {

protected:
    int damage;
    double attackCD;
    double attackrate;

    Manager* pGame;
    shared_ptr<Hero> pHero;
    shared_ptr<Sprite> sprite;


public:
    Zombie(double xIn, double yIn, double speedIn, double damageIn, double hpIn, Manager* pIn, shared_ptr<Hero> pHeroIn, shared_ptr<Sprite> spIn);
    Zombie();
    vector<shared_ptr<Hp_Kit>> bonuses;
    vector<shared_ptr<Shield>> bonuses_1;

    virtual void draw_Zombie() { };
    virtual void createBonus(shared_ptr<Zombie> object) { };
    virtual void DrawHPBar() { };
    virtual void zombie_Attack(float fElapsedTime) { };
    virtual bool isHit(int i) { return false; };
    virtual void move_Zombie(float fElapsedTime) { };

    bool is_Killed();
    void hpCurrent();
    double distance(double x1, double y1, double x2, double y2);
};