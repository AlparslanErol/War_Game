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
#include "Regular_Zombie.h"
#include "Advanced_Zombie.h"

#define PI 3.14159265359
using namespace std;


class Sprite;
class Hero;
class Bullet;
class Regular_Zombie;
class Advanced_Zombie;


class Manager : public olc::PixelGameEngine {

private:
	double spawnRate;
	double spawnCD;
	double spawnRate_1;
	double spawnCD_1;
	double gameTime;
	bool gameEnd;
	int level;

	shared_ptr<Sprite> sprite;
	shared_ptr<Hero> pHero;
	shared_ptr<Regular_Zombie> enemy;
	shared_ptr<Advanced_Zombie> enemy_1;

public:
	Manager();
	vector<shared_ptr<Regular_Zombie>> enemies;
	vector<shared_ptr<Advanced_Zombie>> enemies_1;

	bool OnUserCreate(); //override
	bool OnUserUpdate(float fElapsedTime); //override
	int Level();
};