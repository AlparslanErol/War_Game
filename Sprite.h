#pragma once
#include"Manager.h"
#include<vector>
#include<memory>
using namespace std;

class Sprite {

private:

public:
	Sprite();
	vector<shared_ptr<olc::Sprite>> levelSprites;
	shared_ptr<olc::Sprite> zombieSprite;
	shared_ptr<olc::Sprite> deadSprite;
	shared_ptr<olc::Sprite> bonusSprite;
	shared_ptr<olc::Sprite> manSprite;
};