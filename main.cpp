//olcPixelGameEngine is being developed and shared for education purposes by javidx9 in OneLoneCoder Youtube Channel:
//https://www.youtube.com/channel/UC-yuWVUplUJZvieEligKBkA/about
//olcSimpleEngine is based on olcPixelGameEngine and simplified and modified by Bahadir Pamuk for IE201 course in Industrial Engineering Department of Bogazici University
//olcSimpleEngine.cpp is created in order to resolve object orientation issues, from now on sprites (from olc::Sprite) can be created inside other classes, independently
//Last Edit Date: 03.02.2020

#include "Manager.h"

/*
#include "olcSimpleEngine.h"
#include "olcPGEX_Graphics2D.h"
#include "vector"
#include "Manager.h"

#define PI 3.14159265359
using namespace std;


struct Bullet{
    double x;
    double y;
    double dirX;
    double dirY;
    double speed;
    double damage;
    Bullet(double xIn, double yIn, double dirXIn, double dirYIn, double speedIn, double damageIn)
    {
        x = xIn;
        y = yIn;
        dirX = dirXIn;
        dirY = dirYIn;
        speed = speedIn;
        damage = damageIn;
    }
};

struct Bonus {
    double x;
    double y;

    Bonus(double xIn, double yIn ) {

        x = xIn;
        y = yIn;
    }

};

struct Enemy {
    double x;
    double y;
    double speed;
    double damage;
    double hp;
    double hpmax;
    double attackCD;
    double attackrate;

    Enemy(double xIn, double yIn, double speedIn, double damageIn, double hpIn):attackCD(0),attackrate(2)
    {
        x = xIn;
        y = yIn;
        speed = speedIn;
        damage = damageIn;
        hpmax = hpIn;
        hp = hpmax;
    }
};

double distance(double x1, double y1 , double x2, double y2)
{
    return sqrt(pow(x1-x2,2) + pow (y1- y2,2));
}

class ShootingGame : public olc::PixelGameEngine
{
    double x;
    double y;
    double heroSpeed;
    double hpmax;
    double hpcurr;
    double spawnRate;
    double spawnCD;

    vector<Bullet> bullets;
    vector<Enemy> enemies;
    vector<Bonus> bonuses;
    
    shared_ptr<olc::Sprite> bonusSprite;
    shared_ptr<olc::Sprite> manSprite;
    vector<shared_ptr<olc::Sprite>> levelSprites;
    shared_ptr<olc::Sprite> deadSprite;
    shared_ptr<olc::Sprite> zombieSprite;


    int level;
    double gameTime;
    bool gameEnd;

    void DrawHPBar(int x, int y, int HPMax, int HPCurrent)
    {
        double ratio = (double)(HPCurrent) / (double)HPMax;
        for (int i = x - 5; i < 5 + x; ++i)
            if (i < x - 5 + ratio * 10)
                DrawRect(i, y + 14, 1,1, olc::GREEN);
            else
                DrawRect(i, y + 14, 1,1, olc::RED);
    }




public:
    bool OnUserCreate() //override
    {
        manSprite = make_shared<olc::Sprite>("Sprites/ManTrans.png");
        deadSprite = make_shared<olc::Sprite>("Sprites/Dead.png");
        zombieSprite = make_shared<olc::Sprite>("Sprites/zombie.png");
        bonusSprite = make_shared<olc::Sprite>("Sprites/firstaid.png");
        
        x = ScreenWidth() / 2;
        y = ScreenHeight() / 2;
        heroSpeed = 100;
        
        spawnRate = 5;
        spawnCD = 0;
        
        hpmax = 100;
        hpcurr = 50;
        
        gameTime = 0;
        gameEnd = false;
        
        for (int i = 0; i < 7; ++i)
            levelSprites.push_back(make_shared<olc::Sprite>("Sprites/Level" + to_string(i + 1) + ".png"));

        srand(NULL);
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) //override
    {
      
        if (gameEnd) {
            DrawSprite(0, 0, deadSprite, 1);
            DrawString(ScreenWidth() / 2 - 38, ScreenHeight() / 2 -10, "GAME OVER",olc::DARK_RED);
            DrawString(ScreenWidth() / 2 - 38, ScreenHeight() / 2 , "Try again?", olc::BLACK);
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
        if (spawnCD <= 0)
        {
            double degree = rand() * 360;
            enemies.push_back(Enemy((cos(degree) * ScreenWidth()) + (ScreenWidth() / 2), (sin(degree) * ScreenHeight()) +  (ScreenHeight() / 2),50,10,10));
            spawnCD = spawnRate;
        }
        //ZOMBIE SPAWNS
        
        
        //SHOOTING
        if (GetKey(olc::SPACE).bPressed)
        {
            double dirX = GetMouseX() - x;
            double dirY = GetMouseY() - y;
            double dist = sqrt((dirX * dirX) + (dirY * dirY));
            bullets.push_back(Bullet(x, y, dirX / dist , dirY / dist, 200, 1));
        }
        //SHOOTING


        //UPDATE VARIABLES
        if (GetKey(olc::W).bHeld)
            y -= fElapsedTime * heroSpeed;
        if (GetKey(olc::S).bHeld)
            y += fElapsedTime* heroSpeed;
        if (GetKey(olc::D).bHeld)
            x += fElapsedTime * heroSpeed;
        if (GetKey(olc::A).bHeld)
            x -= fElapsedTime * heroSpeed;
        //UPDATE VARIABLES

        //KEEP HERO IN WINDOW
        if (y <= 0) { y = 0; }
        if (x <= 0) { x = 0; }
        if (y >= ScreenHeight()-1) { y = ScreenHeight()-1; }
        if (x >= ScreenWidth()-1) { x = ScreenWidth()-1; }
        //KEEP HERO IN WINDOW


        //BULLETSMOVE
        for (int i = 0 ; i < bullets.size() ; ++i)
        {
            bullets[i].x += bullets[i].dirX * bullets[i].speed * fElapsedTime;
            bullets[i].y += bullets[i].dirY * bullets[i].speed * fElapsedTime;
            if (bullets[i].x < 0 || bullets[i].x > ScreenWidth() || bullets[i].y < 0 || bullets[i].y > ScreenHeight())
            {
                bullets.erase(bullets.begin() + i);
                i--;
            }
        }
        //BULLETSMOVE


        //BULLETSHIT
        for (int i = 0; i < bullets.size(); ++i)
        {
            for (int j = 0; j < enemies.size(); ++j)
            {
                if (distance(bullets[i].x, bullets[i].y, enemies[j].x, enemies[j].y) < 10)
                {
                    enemies[j].hp -= bullets[i].damage;
                    bullets.erase(bullets.begin() + i);
                    i--;
                    if(enemies[j].hp <= 0)
                    {
                        //RANDOM BONUS CREATION

                        if ( rand()%5 < 1 ) {
                        
                            bonuses.push_back(Bonus(enemies[j].x, enemies[j].y));
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

        for (int i =0 ; i< bonuses.size(); i++)
        {
            if (distance(x,y,bonuses[i].x,bonuses[i].y) <=  10)
            {
                
                if (hpcurr + 20 < hpmax)
                {
                    hpcurr += 20;
                }
                else
                {
                    hpcurr = hpmax;
                }

                bonuses.erase(bonuses.begin() + i);
                i--;

            }

        }

        //BONUS PICK UP









        //ENEMIESMOVE
        for (int i = 0; i < enemies.size(); ++i)
        {
            double dirX =  x - enemies[i].x;
            double dirY =  y - enemies[i].y;
            double dist = sqrt((dirX * dirX) + (dirY * dirY));
            enemies[i].x += dirX / dist * enemies[i].speed * fElapsedTime;
            enemies[i].y += dirY / dist * enemies[i].speed * fElapsedTime;
            if (enemies[i].hp <= 0)
            {
                enemies.erase(enemies.begin() + i);
                i--;
            }
        }
        //ENEMIESMOVE

        //ENEMIESATTACK
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].attackCD -= fElapsedTime;

            if ((distance(enemies[i].x, enemies[i].y, x, y) <= 8) && (enemies[i].attackCD <= 0))
            {
                hpcurr -= enemies[i].damage;
                enemies[i].attackCD = enemies[i].attackrate;
            }
        }

        //ENEMIESATTACK

        //CHECKGAMEOVER


        // If HP is less than 0 or if you press E end game
        if (hpcurr<=0 || GetKey(olc::E).bReleased)
        {

            for (int i = 0; i < enemies.size(); i++)
            {
                enemies.erase(enemies.begin());
                i--;
            }

            for (int i = 0; i < bullets.size(); i++)
            {
                bullets.erase(bullets.begin());
                i--;
            }
            

            for (int i = 0; i < bonuses.size(); i++)
            {
                bonuses.erase(bonuses.begin());
                i--;
            }

            gameEnd=true;
        
        
        }


            //TO BE IMPLEMENTED
        //CHECKGAMEOVER


        //DRAWING

        //THE PLAYER
        Clear(olc::BLACK);
        DrawSprite(0, 0, levelSprites[level - 1],1);
        SetPixelMode(olc::Pixel::ALPHA);
        olc::GFX2D::Transform2D t;
        t.Translate(-manSprite->width / 2, -manSprite->height / 2);
        t.Rotate(atan2((GetMouseX()-x),(GetMouseY() - y)) - PI / 2);
        t.Translate(x, y );
        olc::GFX2D::DrawSprite(manSprite.get(), t);
      
        
        //CROSSHAIR
        DrawLine(GetMouseX() - 5, GetMouseY(), GetMouseX() + 5, GetMouseY(), olc::RED);
        DrawLine(GetMouseX(), GetMouseY() - 5, GetMouseX(), GetMouseY() + 5, olc::RED);
        //CROSSHAIR

        //DRAW BULLETS
        for (auto a: bullets)
            DrawCircle(a.x, a.y, 1,olc::YELLOW);
        
        //DRAW ENEMIES
        for (auto a : enemies) {
            DrawSprite(a.x-12,a.y-12,zombieSprite,1);
            //DrawCircle(a.x, a.y, 1, olc::RED);
            DrawHPBar(a.x, a.y, a.hpmax , a.hp);
        }

        //DRAW BONUSES
        for (auto a: bonuses )
        {
            DrawSprite(a.x - 10, a.y -10, bonusSprite, 1);
        }

        //DRAW HP BAR
        DrawHPBar(x, y - 20, hpmax, hpcurr);

        //DRAWING
        return true;
    }

};
*/

int main()
{
    //ORIGINAL GAME
    /*ShootingGame demo;
    if (demo.Construct(240, 240, 3, 3))
        demo.Start();
        */

    //MY GAME
    Manager game;
    if (game.Construct(240,240,3,3))
        game.Start();
  

    return 0;
}