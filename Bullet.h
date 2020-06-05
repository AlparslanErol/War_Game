#pragma once
#include "Manager.h"
#include <vector>
#include <memory>
using namespace std;

class Manager;

class Bullet
{

private:
    double x;
    double y;
    double dirX;
    double dirY;
    double speed;
    double damage;
    Manager* pGame;

public:

    Bullet(double xIn, double yIn, double dirXIn, double dirYIn, double speedIn, double damageIn, Manager* pIn);

    bool isCollide(double xIn, double yIn);
    void draw_Bullet();
    void bullet_move(float fElapsedTime);
    bool erase();
    double distance(double x1, double y1, double x2, double y2);
};

