#include "Bullet.h"

Bullet::Bullet(double xIn, double yIn, double dirXIn, double dirYIn, double speedIn, double damageIn) {
    x = xIn;
    y = yIn;
    dirX = dirXIn;
    dirY = dirYIn;
    speed = speedIn;
    damage = damageIn;
    bullets = vector<Bullet>();
}

Bullet::~Bullet() {
    delete this;
}


bool Bullet::OnUserUpdate(float fElapsedTime) {

    //BULLETSMOVE
    for (int i = 0; i < bullets.size(); ++i)
    {
        bullets[i].x += bullets[i].dirX * bullets[i].speed * fElapsedTime;
        bullets[i].y += bullets[i].dirY * bullets[i].speed * fElapsedTime;
        if (bullets[i].x < 0 || bullets[i].x > Manager::WIDTH || bullets[i].y < 0 || bullets[i].y > Manager::HEIGHT)
        {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
    //BULLETSMOVE
    return true;
}


double Bullet::getX() {
    return x;
}

double Bullet::getY() {
    return y;
}

double Bullet::setX(double _) {
    return x = _;
}

double Bullet::setY(double _) {
    return y = _;
}

double Bullet::getDamage() {
    return damage;
}

double Bullet::setDamage(double _) {
    return damage = _;
}

double Bullet::getDirX() {
    return dirX;
}

double Bullet::setDirX(double _) {
    return dirX = _;
}

double Bullet::getDirY() {
    return dirY;
}

double Bullet::setDirY(double _) {
    return dirY = _;
}

double Bullet::getSpeed() {
    return speed;
}

double Bullet::setSpeed(double _) {
    return speed = _;
}