#include"Hero.h"

Hero::Hero(double xIn, double yIn, double speedIn, double hpMaxIn, double hpcurrIn, Manager* pIn, shared_ptr<Sprite> spIn)
{
    pGame = pIn;
    sprite = spIn;

    x = xIn;
    y = yIn;
    speed = speedIn;
    hpmax = hpMaxIn;
    hpcurrent = hpcurrIn;

    bullets = vector<shared_ptr<Bullet>>();
}

void Hero::shooting()
{
    //SHOOTING
    if (pGame->GetKey(olc::SPACE).bPressed)
    {
        double dirX = pGame->GetMouseX() - x;
        double dirY = pGame->GetMouseY() - y;
        double dist = sqrt((dirX * dirX) + (dirY * dirY));
        bullets.push_back(make_shared<Bullet>(x, y, dirX / dist, dirY / dist, 200, 1, pGame));
    }
    //SHOOTING
}

void Hero::attractZombie(double* xIn, double* yIn, double speedIn, float fElapsedTimeIn)
{
    double dirX = x - *xIn;
    double dirY = y - *yIn;
    double dist = sqrt((dirX * dirX) + (dirY * dirY));
    *xIn += dirX / dist * speedIn * fElapsedTimeIn;
    *yIn += dirY / dist * speedIn * fElapsedTimeIn;
}
bool Hero::isCollide(double xIn, double yIn)
{
    if (distance(x, y, xIn, yIn) < 10)
    {
        return true;
    }
    return false;
}

void Hero::hpCurrent(double damageIn)
{
    hpcurrent -= damageIn;
}

void Hero::pick_bonus()
{
    if (hpcurrent + 20 < hpmax)
    {
        hpcurrent = hpcurrent + 20;
    }
    else
    {
        hpcurrent = hpmax;
    }
}

void Hero::draw_hero()
{
    pGame->Clear(olc::BLACK);
    pGame->DrawSprite(0, 0, sprite->levelSprites[pGame->Level()], 1);
    pGame->SetPixelMode(olc::Pixel::ALPHA);
    olc::GFX2D::Transform2D t;
    t.Translate(-sprite->manSprite->width / 2, -sprite->manSprite->height / 2);
    t.Rotate(atan2((pGame->GetMouseX() -x), (pGame->GetMouseY() - y)) - PI / 2);
    t.Translate(x,y);
    olc::GFX2D::DrawSprite(sprite->manSprite.get(), t);
}

void Hero::update_hero(float fElapsedTime)
{
    //UPDATE VARIABLES
    if (pGame->GetKey(olc::W).bHeld)
        y -= fElapsedTime * speed;
    if (pGame->GetKey(olc::S).bHeld)
        y += fElapsedTime * speed;
    if (pGame->GetKey(olc::D).bHeld)
        x += fElapsedTime * speed;
    if (pGame->GetKey(olc::A).bHeld)
        x -= fElapsedTime * speed;
    //UPDATE VARIABLES
}

bool Hero::is_Killed()
{
    if (hpcurrent <= 0)
    {
        return true;
    }
    return false;
}

void Hero::hero_keep()
{
    //KEEP HERO IN WINDOW
    if (y <= 0) { y = 0; }
    if (x <= 0) { x = 0; }
    if (y >= pGame->ScreenHeight() - 1) { y = pGame->ScreenHeight() - 1; }
    if (x >= pGame->ScreenWidth() - 1) { x = pGame->ScreenWidth() - 1; }
    //KEEP HERO IN WINDOW
}

double Hero::distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void Hero::DrawHPBar()
{
    double ratio = (double)(hpcurrent) / (double)hpmax;
    for (int i = x - 5; i < 5 + x; ++i)
        if (i < x - 5 + ratio * 10)
            pGame->DrawRect(i, y + 14, 1, 1, olc::GREEN);
        else
            pGame->DrawRect(i, y + 14, 1, 1, olc::RED);
}