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

    void draw_Bullet();
    void bullet_move(float fElapsedTime);

    double getX();
    double getY();
    double getDamage();
    double get_dirX();
    double get_dirY();
    double getSpeed();

    void setX(double _);
    void setY(double _);
};

