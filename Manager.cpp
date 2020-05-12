#include "Manager.h"

Manager::Manager()
{
    pHero = shared_ptr<Hero>();
    sprite = shared_ptr<Sprite>();
    enemies = vector<shared_ptr<Zombie>>();
    bonuses = vector<shared_ptr<Bonus>>();
}

bool Manager::OnUserCreate()
{
    sprite = make_shared<Sprite>();
    pHero = make_shared<Hero>(ScreenWidth() / 2, ScreenHeight() / 2, 100, 100, 50, this, sprite);

    spawnRate = 5;
    spawnCD = 0;

    gameTime = 0;
    gameEnd = false;
    level = 0;

    srand(NULL);
    return true;
}

bool Manager::OnUserUpdate(float fElapsedTime)
{
    if (gameEnd) {
        DrawSprite(0, 0, sprite->deadSprite, 1);
        DrawString(ScreenWidth() / 2 - 38, ScreenHeight() / 2 - 10, "GAME OVER", olc::DARK_RED);
        DrawString(ScreenWidth() / 2 - 38, ScreenHeight() / 2, "Try again?", olc::BLACK);
        DrawString(ScreenWidth() / 2 - 35, ScreenHeight() / 2 + 10, "Press Y", olc::BLACK);
        DrawString(ScreenWidth() / 2 - 55, ScreenHeight() / 2 + 20, "Press N to exit", olc::BLACK);

        if (GetKey(olc::Y).bPressed)
        {
            OnUserCreate();
        }
        if (GetKey(olc::Key::N).bPressed)
            return false;

        return true;
    }

    gameTime += fElapsedTime;
    level = int(gameTime / 10) % 7 + 1;

    //ZOMBIE SPAWNS
    spawnCD -= fElapsedTime;
    double degree = rand() * 360;
    if (spawnCD <= 0)
    {
        enemies.push_back(make_shared<Zombie>((cos(degree) * ScreenWidth()) + (ScreenWidth() / 2), (sin(degree) * ScreenHeight()) + (ScreenHeight() / 2), 50, 10, 10, this, pHero, sprite));
        spawnCD = spawnRate;
    }
    //ZOMBIE SPAWNS

    pHero->shooting();
    pHero->update_hero(fElapsedTime);
    pHero->hero_keep();

    //BULLETSMOVE
    for (int i = 0; i < pHero->bullets.size(); ++i)
    {
        pHero->bullets[i]->bullet_move(fElapsedTime);
        if (pHero->bullets[i]->getX() < 0 || pHero->bullets[i]->getX() > ScreenWidth() || pHero->bullets[i]->getY() < 0 || pHero->bullets[i]->getY() > ScreenHeight())
        {
            pHero->bullets.erase(pHero->bullets.begin() + i);
            i--;
        }
    }
    //BULLETSMOVE

    //BULLETSHIT
    for (int i = 0; i < pHero->bullets.size(); ++i)
    {
        for (int j = 0; j < enemies.size(); ++j)
        {
            if (distance(pHero->bullets[i]->getX(), pHero->bullets[i]->getY(), enemies[j]->getX(), enemies[j]->getY()) < 10)
            {
                enemies[j]->setHpcurrent(enemies[j]->getHpcurrent() - pHero->bullets[i]->getDamage());
                pHero->bullets.erase(pHero->bullets.begin() + i);
                i--;
                if (enemies[j]->getHpcurrent() <= 0)
                {
                    //RANDOM BONUS CREATION
                    if (rand() % 5 < 1) 
                    {
                        bonuses.push_back(make_shared<Bonus>(enemies[j]->getX(), enemies[j]->getY(), this, sprite, pHero));
                    }
                    //RANDOM BONUS CREATION
                    enemies.erase(enemies.begin() + j);
                    j--;
                }
                break;
            }
        }
    }
    //BULLETSHIT

    //BONUS PICK UP
    for (int i = 0; i < bonuses.size(); i++)
    {
        if (bonuses[i]->is_picked())
        {
            pHero->pick_bonus();
            bonuses.erase(bonuses.begin() + i);
            i--;
        }
    }
    //BONUS PICK UP

    //ENEMIESMOVE
    for (int i = 0; i < enemies.size(); ++i)
    {
        enemies[i]->move_Zombie(fElapsedTime);
        if (enemies[i]->is_Killed())
        {
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }
    //ENEMIESMOVE

    //ENEMIESATTACK
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->zombie_Attack(fElapsedTime);
    //ENEMIESATTACK

    //CHECKGAMEOVER
    // If HP is less than 0 or if you press E end game
    if (pHero->getHpcurrent() <= 0 || GetKey(olc::E).bReleased)
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies.erase(enemies.begin());
            i--;
        }
        for (int i = 0; i < pHero->bullets.size(); i++)
        {
            pHero->bullets.erase(pHero->bullets.begin());
            i--;
        }
        for (int i = 0; i < bonuses.size(); i++)
        {
            bonuses.erase(bonuses.begin());
            i--;
        }
        gameEnd = true;
    }
    //TO BE IMPLEMENTED
    //CHECKGAMEOVER


    //DRAWING

    //HERO and BACKGROUND
    pHero->draw_hero();
    //HERO and BACKGROUND

    //CROSSHAIR
    DrawLine(GetMouseX() - 5, GetMouseY(), GetMouseX() + 5, GetMouseY(), olc::RED);
    DrawLine(GetMouseX(), GetMouseY() - 5, GetMouseX(), GetMouseY() + 5, olc::RED);
    //CROSSHAIR

    //DRAW BULLETS
    for (auto a : pHero->bullets)
        a->draw_Bullet();
    //DRAW BULLETS

    //DRAW ENEMIES
    for (auto a : enemies) {
        a->draw_Zombie();
        a->DrawHPBar(a->getX(), a->getY(), a->getHpmax(), a->getHpcurrent());
    }
    //DRAW ENEMIES

    //DRAW BONUSES
    for (auto a : bonuses)
    {
        a->draw_Bonus();
    }
    //DRAW BONUSES

    //DRAW HP BAR HERO
    pHero->DrawHPBar(pHero->getX(), pHero->getY(), pHero->getHpmax(), pHero->getHpcurrent());
    //DRAW HP BAR HERO

// DRAWING END

    return true;
}

double Manager::distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int Manager::getLevel()
{
    return level;
}

void Manager::setLevel(int _)
{
    level = _;
}