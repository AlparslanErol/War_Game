#include"Sprite.h"

Sprite::Sprite() {
	levelSprites = vector<shared_ptr<olc::Sprite>>();
	for (int i = 0; i < 7; ++i)
		levelSprites.push_back(make_shared<olc::Sprite>("Sprites/Level" + to_string(i + 1) + ".png"));

	manSprite = shared_ptr<olc::Sprite>();
	deadSprite = shared_ptr<olc::Sprite>();
	zombieSprite = shared_ptr<olc::Sprite>();
	bonusSprite = shared_ptr<olc::Sprite>();

    manSprite = make_shared<olc::Sprite>("Sprites/ManTrans.png");
    deadSprite = make_shared<olc::Sprite>("Sprites/Dead.png");
    zombieSprite = make_shared<olc::Sprite>("Sprites/zombie.png");
    bonusSprite = make_shared<olc::Sprite>("Sprites/firstaid.png");
}