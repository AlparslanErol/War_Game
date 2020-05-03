#include "Manager.h"

Manager::Manager() {
}

Manager::~Manager() {
}


void Manager::DrawHPBar(int x, int y, int HPMax, int HPCurrent)
{
    double ratio = (double)(HPCurrent) / (double)HPMax;
    for (int i = x - 5; i < 5 + x; ++i)
        if (i < x - 5 + ratio * 10)
            DrawRect(i, y + 14, 1, 1, olc::GREEN);
        else
            DrawRect(i, y + 14, 1, 1, olc::RED);
}


bool Manager::OnUserCreate() {

    double degree = rand() * 360;

    frame = new Background();
    hero = new Hero();
    bonus = new Bonus(0, 0, hero);
    bullet = new Bullet(0, 0, 0, 0, 0, 0);
    enemy = new Enemy((cos(degree) * WIDTH) + (WIDTH / 2), (sin(degree) * HEIGHT) + (HEIGHT / 2), 50, 10, 10, hero, bullet, bonus);

    deadSprite = std::shared_ptr<olc::Sprite>();
    deadSprite = make_shared<olc::Sprite>("Sprites/Dead.png");

    gameTime = 0;
    gameEnd = false;
    level = 0;

    srand(NULL);
    return true;
}


bool Manager::OnUserUpdate(float fElapsedTime) {

    hero->OnUserUpdate(fElapsedTime);
    bonus->OnUserUpdate(fElapsedTime);
    bullet->OnUserUpdate(fElapsedTime);
    enemy->OnUserUpdate(fElapsedTime);

    if (gameEnd) {
        DrawSprite(0, 0, deadSprite, 1);
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


    //SHOOTING
    if (GetKey(olc::SPACE).bPressed)
    {
        double dirX = GetMouseX() - hero->getX();
        double dirY = GetMouseY() - hero->getY();
        double dist = sqrt((dirX * dirX) + (dirY * dirY));
        bullet->bullets.push_back(Bullet(hero->getX(), hero->getY(), dirX / dist, dirY / dist, 200, 1));
    }
    //SHOOTING


    //UPDATE VARIABLES
    if (GetKey(olc::W).bHeld)
        hero->setY(hero->getY() - fElapsedTime * hero->getHeroSpeed());
    if (GetKey(olc::S).bHeld)
        hero->setY(hero->getY() + fElapsedTime * hero->getHeroSpeed());
    if (GetKey(olc::D).bHeld)
        hero->setX(hero->getX() + fElapsedTime * hero->getHeroSpeed());
    if (GetKey(olc::A).bHeld)
        hero->setX(hero->getX() - fElapsedTime * hero->getHeroSpeed());
    //UPDATE VARIABLES


    //KEEP HERO IN WINDOW
    if (hero->getY() <= 0) { hero->setY(0); }
    if (hero->getX() <= 0) { hero->setX(0); }
    if (hero->getY() >= ScreenHeight()) { hero->setY(ScreenHeight()); }
    if (hero->getX() >= ScreenWidth()) { hero->setX(ScreenHeight()); }
    //KEEP HERO IN WINDOW


    // If HP is less than 0 or if you press E end game
    if (hero->getHpCurr() <= 0 || GetKey(olc::E).bReleased) {
        for (int i = 0; i < enemy->enemies.size(); i++)
        {
            enemy->enemies.erase(enemy->enemies.begin());
            i--;
        }

        for (int i = 0; i < bullet->bullets.size(); i++)
        {
            bullet->bullets.erase(bullet->bullets.begin());
            i--;
        }

        for (int i = 0; i < bonus->bonuses.size(); i++)
        {
            bonus->bonuses.erase(bonus->bonuses.begin());
            i--;
        }
        gameEnd = true;
    }
    //TO BE IMPLEMENTED
    //CHECKGAMEOVER


    //DRAWING
    //THE PLAYER
    Clear(olc::BLACK);
    DrawSprite(0, 0, frame->levelSprites[level - 1], 1);
    SetPixelMode(olc::Pixel::ALPHA);
    olc::GFX2D::Transform2D t;
    t.Translate(-hero->manSprite->width / 2, -hero->manSprite->height / 2);
    t.Rotate(atan2((GetMouseX() - hero->getX()), (GetMouseY() - hero->getY())) - PI / 2);
    t.Translate(hero->getX(), hero->getY());
    olc::GFX2D::DrawSprite(hero->manSprite.get(), t);
    //THE PLAYER


     //CROSSHAIR
    DrawLine(GetMouseX() - 5, GetMouseY(), GetMouseX() + 5, GetMouseY(), olc::RED);
    DrawLine(GetMouseX(), GetMouseY() - 5, GetMouseX(), GetMouseY() + 5, olc::RED);
    //CROSSHAIR


    //DRAW BULLETS
    for (auto a : bullet->bullets)
        DrawCircle(a.getX(), a.getY(), 1, olc::YELLOW);
    //DRAW BULLETS


    //DRAW ENEMIES
    for (auto a : enemy->enemies) {
        DrawSprite(a.getX() - 12, a.getY() - 12, enemy->zombieSprite, 1);
        //DrawCircle(a.x, a.y, 1, olc::RED);
        DrawHPBar(a.getX(), a.getY(), a.getHpMax(), a.getHpCurr());
    }
    //DRAW ENEMIES


    //DRAW BONUSES
    for (auto a : bonus->bonuses)
    {
        DrawSprite(a.getX() - 10, a.getY() - 10, bonus->bonusSprite, 1);
    }
    //DRAW BONUSES


    //DRAW HP BAR
    DrawHPBar(hero->getX(), hero->getY() - 20, hero->getHpMax(), hero->getHpCurr());
    //DRAW HP BAR

    //DRAWING

    return true;
}