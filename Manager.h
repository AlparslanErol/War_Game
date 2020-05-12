#pragma once
#include "olcSimpleEngine.h"
#include "olcPGEX_Graphics2D.h"
#include <vector>
#include <memory>
#include "Human.h"
#include "bullet.h"
#include "bonus.h"
#include "Hero.h"
#include "Zombie.h"
#include "Sprite.h"
#define PI 3.14159265359
using namespace std;


class Human;
class Sprite;
class Hero;
class Bullet;
class Zombie;
class Bonus;

class Manager : public olc::PixelGameEngine {

private:
	double spawnRate;
	double spawnCD;
	double gameTime;
	bool gameEnd;
	int level;

	shared_ptr<Sprite> sprite;
	shared_ptr<Hero> pHero;

public:
	Manager();

	vector<shared_ptr<Bonus>> bonuses;
	vector<shared_ptr<Zombie>> enemies;

	bool OnUserCreate(); //override
	bool OnUserUpdate(float fElapsedTime); //override
	double distance(double x1, double y1, double x2, double y2);

	int getLevel();
	void setLevel(int _);
};
