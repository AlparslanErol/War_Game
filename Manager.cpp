#include "Manager.h"

Manager::Manager()
{
    pHero = shared_ptr<Hero>();
    sprite = shared_ptr<Sprite>();

    enemy = shared_ptr<Regular_Zombie>();
    enemy_1 = shared_ptr<Advanced_Zombie>();

    enemies = vector<shared_ptr<Regular_Zombie>>();
    enemies_1 = vector<shared_ptr<Advanced_Zombie>>();
}

bool Manager::OnUserCreate()
{
    sprite = make_shared<Sprite>();
    pHero = make_shared<Hero>(ScreenWidth() / 2, ScreenHeight() / 2, 100, 100, 50, this, sprite);

    enemy = make_shared<Regular_Zombie>(0, 0, 0, 0, 0, this, pHero, sprite);
    enemy_1 = make_shared<Advanced_Zombie>(0, 0, 0, 0, 0, this, pHero, sprite);

    spawnRate = 5;
    spawnCD = 0;
    spawnRate_1 = 10;
    spawnCD_1 = 0;

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
    spawnCD_1 -= fElapsedTime;
    double degree = rand() * 360;
    if (spawnCD <= 0)
    {
        enemies.push_back(make_shared<Regular_Zombie>((cos(degree) * ScreenWidth()) + (ScreenWidth() / 2), (sin(degree) * ScreenHeight()) + (ScreenHeight() / 2), 50, 10, 10, this, pHero, sprite));
        spawnCD = spawnRate;
    }
    if (spawnCD_1 <= 0)
    {
        enemies_1.push_back(make_shared<Advanced_Zombie>((cos(degree) * ScreenWidth()) + (ScreenWidth() / 2), (sin(degree) * ScreenHeight()) + (ScreenHeight() / 2), 25, 20, 20, this, pHero, sprite));
        spawnCD_1 = spawnRate_1;
    }
    //ZOMBIE SPAWNS


    pHero->shooting();
    pHero->update_hero(fElapsedTime);
    pHero->hero_keep();
    

    //BULLETSMOVE
    for (int i = 0; i < pHero->bullets.size(); ++i)
    {
        pHero->bullets[i]->bullet_move(fElapsedTime);
        if (pHero->bullets[i]->erase())
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
            if(enemies[j]->isHit(i))
            {
                enemies[j]->hpCurrent();
                pHero->bullets.erase(pHero->bullets.begin() + i);
                i--;
                if (enemies[j]->is_Killed())
                {
                    //RANDOM BONUS CREATION
                    if (rand() % 5 < 1)
                    {
                        enemy->createBonus(enemies[j]);
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
    //BULLETSHIT
    for (int i = 0; i < pHero->bullets.size(); ++i)
    {
        for (int j = 0; j < enemies_1.size(); ++j)
        {
            if (enemies_1[j]->isHit(i))
            {
                enemies_1[j]->hpCurrent();
                pHero->bullets.erase(pHero->bullets.begin() + i);
                i--;
                if (enemies_1[j]->is_Killed())
                {
                    //RANDOM BONUS CREATION
                    if (true)
                    {
                        enemy_1->createBonus(enemies_1[j]);
                    }
                    //RANDOM BONUS CREATION
                    enemies_1.erase(enemies_1.begin() + j);
                    j--;
                }
                break;
            }
        }
    }
    //BULLETSHIT


    //BONUS PICK UP
    for (int i = 0; i < enemy->bonuses.size(); i++)
    {
        if (enemy->bonuses[i]->is_picked())
        {
            pHero->pick_bonus();
            enemy->bonuses.erase(enemy->bonuses.begin() + i);
            i--;
        }
    }
    //BONUS PICK UP
    //BONUS PICK UP
    for (int i = 0; i < enemy_1->bonuses_1.size(); i++)
    {
        if (enemy_1->bonuses_1[i]->is_picked())
        {
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies.erase(enemies.begin());
                i--;
            }
            for (int i = 0; i < enemies_1.size(); i++)
            {
                enemies_1.erase(enemies_1.begin());
                i--;
            }
            enemy_1->bonuses_1.erase(enemy_1->bonuses_1.begin() + i);
            i--;
        }
    }
    //BONUS PICK UP


    //ENEMIESMOVE
    for (int i = 0; i < enemies.size(); ++i)
    {
        enemies[i]->move_Zombie(fElapsedTime);
    }
    //ENEMIESMOVE
    //ENEMIESMOVE
    for (int i = 0; i < enemies_1.size(); ++i)
    {
        enemies_1[i]->move_Zombie(fElapsedTime);
    }
    //ENEMIESMOVE


    //ENEMIESATTACK
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->zombie_Attack(fElapsedTime);
    //ENEMIESATTACK
    //ENEMIESATTACK
    for (int i = 0; i < enemies_1.size(); i++)
        enemies_1[i]->zombie_Attack(fElapsedTime);
    //ENEMIESATTACK


    //DRAWING

    //HERO and BACKGROUND
    pHero->draw_hero();
    //HERO and BACKGROUND
    //DRAW HP BAR HERO
    pHero->DrawHPBar();
    //DRAW HP BAR HERO

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
        a->DrawHPBar();
    }
    //DRAW ENEMIES
    //DRAW ENEMIES
    for (auto a : enemies_1) {
        a->draw_Zombie();
        a->DrawHPBar();
    }
    //DRAW ENEMIES

    //DRAW BONUSES
    for (auto a : enemy->bonuses)
    {
        a->draw_Bonus();
    }
    //DRAW BONUSES
    //DRAW BONUSES
    for (auto a : enemy_1->bonuses_1)
    {
        a->draw_Bonus();
    }
    //DRAW BONUSES


    // DRAWING END

    //CHECKGAMEOVER
    // If HP is less than 0 or if you press E end game
    if (pHero->is_Killed() || GetKey(olc::E).bReleased)
    {

        for (int i = 0; i < pHero->bullets.size(); i++)
        {
            pHero->bullets.erase(pHero->bullets.begin());
            i--;
        }
        for (int i = 0; i < enemy->bonuses.size(); i++)
        {
            enemy->bonuses.erase(enemy->bonuses.begin());
            i--;
        }
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies.erase(enemies.begin());
            i--;
        }
        for (int i = 0; i < enemies_1.size(); i++)
        {
            enemies_1.erase(enemies_1.begin());
            i--;
        }
        gameEnd = true;
    }
    //TO BE IMPLEMENTED
    //CHECKGAMEOVER

    return true;
}

int Manager::Level()
{
    return level -= 1;
}