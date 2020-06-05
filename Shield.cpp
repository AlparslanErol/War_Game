#include "Shield.h"

Shield::Shield(int xIn, int yIn, Manager* pIn, shared_ptr<Sprite> spIn, shared_ptr<Hero> pHeroIn)
{
	pHero = pHeroIn;
	pGame = pIn;
	sprite = spIn;

	x = xIn;
	y = yIn;
}

void Shield::draw_Bonus()
{
	pGame->DrawSprite(x - 10, y - 10, sprite->bonus1Sprite, 1);
}

bool Shield::is_picked()
{
	//BONUS PICK UP
	if (pHero->isCollide(x, y))
	{
		return true;
	}
	//BONUS PICK UP
	return false;
}