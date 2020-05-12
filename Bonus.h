#pragma once
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;

class Manager;
class Sprite;
class Hero;

class Bonus
{
private:
    int x;
    int y;

    Manager* pGame;
    shared_ptr<Hero> pHero;
    shared_ptr<Sprite> sprite;

public:
    Bonus(int xIn, int yIn, Manager* pIn, shared_ptr<Sprite> spIn, shared_ptr<Hero> pHeroIn);

    void draw_Bonus();
    bool is_picked();
    int getX();
    int getY();
};