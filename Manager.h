#pragma once
#include "olcSimpleEngine.h"
#include "olcPGEX_Graphics2D.h"
#include "vector"
#include "Hero.h"
#include "Bullet.h"
#include "Bonus.h"
#include "Enemy.h"
#include "Background.h"

#define PI 3.14159265359
using namespace std;


class Manager : public olc::PixelGameEngine {

private:
	int level;
	double gameTime;
	bool gameEnd;

	class Hero* hero;
	class Bullet* bullet;
	class Bonus* bonus;
	class Enemy* enemy;
	class Background* frame;

public:
	Manager();
	~Manager();

	std::shared_ptr<olc::Sprite> deadSprite;

	const static int WIDTH = 240;
	const static int HEIGHT = 240;
	
	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime); //override
	void DrawHPBar(int x, int y, int HPMax, int HPCurrent);
};
