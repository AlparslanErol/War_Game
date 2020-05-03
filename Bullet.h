#pragma once
#include "Manager.h"


class Bullet {

private:
    double x;
    double y;
    double dirX;
    double dirY;
    double speed;
    double damage;

public:
    Bullet(double xIn, double yIn, double dirXIn, double dirYIn, double speedIn, double damageIn);
    ~Bullet();
    std::vector<class Bullet> bullets;

    bool OnUserUpdate(float fElapsedTime); //override

    double getX();
    double setX(double _);

    double getY();
    double setY(double _);

    double getDirX();
    double setDirX(double _);

    double getDirY();
    double setDirY(double _);

    double getSpeed();
    double setSpeed(double _);

    double getDamage();
    double setDamage(double _);
};