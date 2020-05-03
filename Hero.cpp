#include "Hero.h"

Hero::Hero() {

	x = Manager::WIDTH / 2;
	y = Manager::HEIGHT / 2;
	heroSpeed = 100;
	hpmax = 100;
	hpcurr = 50;

	manSprite = std::shared_ptr<olc::Sprite>();
	manSprite = make_shared<olc::Sprite>("Sprites/ManTrans.png");
}

Hero::~Hero() {
	
}


bool Hero::OnUserUpdate(float fElapsedTime) {
	return true;
}

double Hero::getX() {
	return x;
}
double Hero::getY() {
   	return y;
}
double Hero::getHeroSpeed() {
	return heroSpeed;
}
double Hero::getHpMax() {
	return hpmax;
}
double Hero::getHpCurr() {
	return hpcurr;
}
double Hero::setX(double _) {
	return x = _;
}
double Hero::setY(double _) {
	return y = _;
}
double Hero::setHeroSpeed(double _) {
	return heroSpeed = _;
}
double Hero::setHpMax(double _) {
	return hpmax = _;
}
double Hero::setHpCurr(double _) {
	return hpcurr = _;
}

