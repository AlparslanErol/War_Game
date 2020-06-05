#pragma once
#include "Zombie.h"
#include "Manager.h"
#include "Shield.h"
#include <vector>
#include <memory>
using namespace std;

class Advanced_Zombie : public Zombie {

public:
    Advanced_Zombie(double xIn, double yIn, double speedIn, double damageIn, double hpIn, Manager* pIn, shared_ptr<Hero> pHeroIn, shared_ptr<Sprite> spIn);

    void draw_Zombie();
    void createBonus(shared_ptr<Advanced_Zombie> object);
    void DrawHPBar();
    void zombie_Attack(float fElapsedTime);
    bool isHit(int i);
    void move_Zombie(float fElapsedTime);
};