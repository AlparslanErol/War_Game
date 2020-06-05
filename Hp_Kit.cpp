#include "Hp_Kit.h"

Hp_Kit::Hp_Kit(int xIn, int yIn, Manager* pIn, shared_ptr<Sprite> spIn, shared_ptr<Hero> pHeroIn)
{
	pHero = pHeroIn;
	pGame = pIn;
	sprite = spIn;

	x = xIn;
	y = yIn;
}

void Hp_Kit::draw_Bonus()
{
	pGame->DrawSprite(x - 10, y - 10, sprite->bonusSprite, 1);
}

bool Hp_Kit::is_picked()
{
	//BONUS PICK UP
	if (pHero->isCollide(x, y))
	{
		return true;
	}
	//BONUS PICK UP

	return false;
}