#include "Enemy.h"

Enemy::Enemy(double xIn, double yIn, double speedIn, double damageIn, double hpIn) {

    x = xIn;
    y = yIn;
    speed = speedIn;
    damage = damageIn;
    hpmax = hpIn;
    hp = hpmax;
    spawnRate = 5;
    spawnCD = 0;
    attackCD = 0;
    attackrate = 2;

    enemies = vector<Enemy>();
    zombieSprite = shared_ptr<olc::Sprite>();
    zombieSprite = make_shared<olc::Sprite>("Sprites/zombie->png");
}

Enemy::~Enemy() {

}


bool Enemy::OnUserUpdate(float fElapsedTime) {

    //ZOMBIE SPAWNS
    spawnCD -= fElapsedTime;
    if (spawnCD <= 0)
    {
        double degree = rand() * 360;
        enemies.push_back(Enemy((cos(degree) * Manager::WIDTH) + (Manager::WIDTH / 2), (sin(degree) * Manager::HEIGHT) + (Manager::HEIGHT / 2), 50, 10, 10));
        spawnCD = spawnRate;
    }
    //ZOMBIE SPAWNS
    
    //BULLETSHIT 
    
    for (int i = 0; i < bullet->bullets.size(); ++i)
    {
        for (int j = 0; j < enemies.size(); ++j)
        {
            if (distance(bullet->bullets[i].getX(), bullet->bullets[i].getY(), enemies[j].x, enemies[j].y) < 10)
            {
                 
                enemies[j].hp -= bullet->bullets[i].getDamage();
                bullet->bullets.erase(bullet->bullets.begin() + i);
                i--;
                if (enemies[j].hp <= 0)
                {
                    //RANDOM BONUS CREATION

                    if (rand() % 5 < 1) {

                        bonus->bonuses.push_back(Bonus(enemies[j].x, enemies[j].y));
                    }
                    //RANDOM BONUS CREATION

                    enemies.erase(enemies.begin() + j);
                    j--;
                }
                break;
            }
        }
    }
    //BULLETSHIT


     //ENEMIESMOVE
    for (int i = 0; i < enemies.size(); ++i)
    {
        double dirX = hero->getX() - enemies[i].getX();
        double dirY = hero->getY() - enemies[i].getY();
        double dist = sqrt((dirX * dirX) + (dirY * dirY));
        enemies[i].x += dirX / dist * enemies[i].speed * fElapsedTime;
        enemies[i].y += dirY / dist * enemies[i].speed * fElapsedTime;
        if (enemies[i].hp <= 0)
        {
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }
    //ENEMIESMOVE


    //ENEMIESATTACK
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].attackCD -= fElapsedTime;

        if ((distance(enemies[i].x, enemies[i].y, x, y) <= 8) && (enemies[i].attackCD <= 0))
        {
            hero->setHpCurr(hero->getHpCurr() - enemies[i].damage);
            enemies[i].attackCD = enemies[i].attackrate;
        }
    }
    //ENEMIESATTACK

    return true;
}

double Enemy::distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double Enemy::getX() {
    return x;
}

double Enemy::getY() {
    return y;
}

double Enemy::getEnemySpeed() {
    return speed;
}

double Enemy::getHpMax() {
    return hpmax;
}

double Enemy::getHpCurr() {
    return hp;
}

double Enemy::setX(double _) {
    return x = _;
}

double Enemy::setY(double _) {
    return y = _;
}

double Enemy::setEnemySpeed(double _) {
    return speed = _;
}

double Enemy::setHpMax(double _) {
    return hpmax = _;
}

double Enemy::setHpCurr(double _) {
    return hp = _;
}

double Enemy::getSpawnRate() {
    return spawnRate;
}

double Enemy::getHpSpawnCD() {
    return spawnCD;
}

double Enemy::setSpawnRate(double _) {
    return spawnRate = _;
}

double Enemy::setHpSpawnCD(double _) {
    return spawnCD = _;
}

double Enemy::getEnemyDamage()
{
    return damage;
}
