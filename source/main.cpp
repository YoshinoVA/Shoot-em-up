#include "AIE.h"
#include <iostream>

int backgroundWidth = 800;
int backgroundHeight = 800;

struct Player
{
	unsigned int iSpriteID;
	float X = backgroundWidth*0.5f;
	float Y = 80.f;
	float Width;
	float Height;
};

struct Enemy
{
	unsigned int iSpriteID; 
	float Width;
	float Height;
	float X;
	float Y;
};

struct Bullet
{

};

Player avatar;
Enemy enemy;
Bullet bullet;

 struct CircleCollider
{
	float radius = 0;
	float centerX = 0;
	float centerY = 0;
 };

int main( int argc, char* argv[] )
{	
    Initialise(backgroundWidth, backgroundHeight, false, "Touhou 15.3");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	int Cirno = CreateSprite("./images/Cirno.png", 45, 50, true);
	int Enemy1 = CreateSprite("./images/BlueFairy.png", 45, 50, true);

	float deltaTime;
    //Game Loop 
    do
    {
			deltaTime = GetDeltaTime();
			if (IsKeyDown('A'))
			{
				avatar.X -= 2.f;
				if (avatar.X < 32.f)
				{
					avatar.X = 32.f;
				}
			}
			if (IsKeyDown('D'))
			{
				avatar.X += 2.f;
				if (avatar.X > 800 - 32.f)
				{
					avatar.X = 800 - 32.f;
				}
			}
			if (IsKeyDown('W'))
			{
				avatar.Y += 2.f;
				if (avatar.Y > 800 - 32.f)
				{
					avatar.Y = 800 - 32.f;
				}
			}
			if (IsKeyDown('S'))
			{
				avatar.Y -= 2.f;
				if (avatar.Y < 32.f)
				{
					avatar.Y = 32.f;
				}
		}


		MoveSprite(Cirno, avatar.X, avatar.Y);
		DrawSprite(Cirno);
		MoveSprite(Enemy1, 400, 700);
		DrawSprite(Enemy1);
        ClearScreen();

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}