#pragma once
#include "Manager.h"
#include "Bonus.h"
#include <vector>
#include <memory>
using namespace std;


class Hp_Kit : public Bonus
{

public:
    Hp_Kit(int xIn, int yIn, Manager* pIn, shared_ptr<Sprite> spIn, shared_ptr<Hero> pHeroIn);
    void draw_Bonus();
    bool is_picked();
};