#pragma once
#include "Manager.h"

class Enemy {

private:
    double x;
    double y;
    double speed;
    double damage;
    double hp;
    double hpmax;   
    double attackCD;
    double attackrate;
    double spawnRate;
    double spawnCD;
    class Hero* hero;
    class Bullet* bullet;
    class Bonus* bonus;

public:
    Enemy(double xIn, double yIn, double speedIn, double damageIn, double hpIn, Hero *heroIn, Bullet *bulletIn, Bonus *bonusIn);
    ~Enemy();

    std::shared_ptr<olc::Sprite> zombieSprite;
    std::vector<class Enemy> enemies;

    bool OnUserUpdate(float fElapsedTime); //override
    double distance(double x1, double y1, double x2, double y2);

    double getX();
    double setX(double _);

    double getY();
    double setY(double _);
    
    double getEnemySpeed();
    double setEnemySpeed(double _);
    
    double getHpMax();
    double setHpMax(double _);
    
    double getHpCurr();
    double setHpCurr(double _);
    
    double getSpawnRate();
    double setSpawnRate(double _);
    
    double getHpSpawnCD();
    double setHpSpawnCD(double _);
    
    double getAttackCD();
    double setAttackCD(double _);
    
    double getAttackRate();
    double setAttackRate(double _);
    
    double getEnemyDamage();
};
