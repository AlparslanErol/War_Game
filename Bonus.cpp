#include"Bonus.h"

Bonus::Bonus(int xIn, int yIn, Manager* pIn, shared_ptr<Sprite> spIn, shared_ptr<Hero> pHeroIn)
{
	pHero = pHeroIn;
	pGame = pIn;
	sprite = spIn;

	x = xIn;
	y = yIn;
}
void Bonus::draw_Bonus()
{
	pGame->DrawSprite(x - 10, y - 10, sprite->bonusSprite, 1);
}

bool Bonus::is_picked()
{
    //BONUS PICK UP
	if (pGame->distance(pHero->getX(), pHero->getY(), x, y) <= 10)
	{
		return true;
	}
    //BONUS PICK UP

	return false;
}

int Bonus::getX()
{
	return x;
}

int Bonus::getY()
{
	return y;
}