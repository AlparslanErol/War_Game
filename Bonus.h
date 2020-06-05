#pragma once
#include <vector>
#include <memory>
using namespace std;

class Manager;
class Sprite;
class Hero;

class Bonus
{
protected:
    int x;
    int y;

    Manager* pGame;
    shared_ptr<Hero> pHero;
    shared_ptr<Sprite> sprite;

public:
    Bonus();
    virtual void draw_Bonus() { };
    virtual bool is_picked() { return false; };
    double distance(double x1, double y1, double x2, double y2);
};