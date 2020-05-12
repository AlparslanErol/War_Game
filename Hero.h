#pragma once
#include "Human.h"
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;

class Human;
class Manager;
class Sprite;
class Bullet;

class Hero : public Human {

private:
    Manager* pGame;
    shared_ptr<Sprite> sprite;

public:
    Hero(double xIn, double yIn, double speedIn, double hpMaxIn, double hpcurrIn, Manager* pIn, shared_ptr<Sprite> spIn);

    vector<shared_ptr<Bullet>> bullets;
    void shooting();
    void pick_bonus();
    void draw_hero();
    void update_hero(float fElapsedTime);
    void hero_keep();

    void DrawHPBar(int x, int y, int HPMax, int HPCurrent);
};