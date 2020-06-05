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

	void shooting();
    void attractZombie(double* xIn, double* yIn, double speedIn, float fElapsedTimeIn);
    bool isCollide(double xIn, double yIn);
	void hpCurrent(double damageIn);
    vector<shared_ptr<Bullet>> bullets;
    void pick_bonus();
    void draw_hero();
    void update_hero(float fElapsedTime);
    bool is_Killed();
    void hero_keep();
    double distance(double x1, double y1, double x2, double y2);
    void DrawHPBar();
};