#include "AIE.h"
#include <vector>
#include <iostream>
#include <math.h>

int backgroundWidth = 800;
int backgroundHeight = 800;

struct CircleCollision
{
	float radius = 0;
};

class Bullet
{
public:
	float xSpeed = 0;
	float ySpeed = 20;
	float x;
	float y;
	CircleCollision bulletCircle;

	int iSpriteID = CreateSprite("./images/Bullet.png", 32, 32, true);

	Bullet()
	{
		bulletCircle.radius = 16;
	}
	~Bullet()
	{

	}

	void SetSpeed(float x_BulletSpeed, float y_BulletSpeed)
	{
		x += x_BulletSpeed;
		y += y_BulletSpeed;
		MoveSprite(iSpriteID, x, y);
		DrawSprite(iSpriteID);
	}
	void move(float aDelta)
	{
		x += xSpeed * aDelta;
		y += ySpeed * aDelta;
	}
};

class Player
{
public:
	unsigned int iSpriteID;
	float X = backgroundWidth*0.5f;
	float Y = 80.f;
	float Width;
	float Height;
	CircleCollision playerCollision;

	std::vector<Bullet> AllBullets;

	void setCircle()
	{
		playerCollision.radius = 25;
	}
};

class Enemy
{
public:
	unsigned int iSpriteID;
	float Width;
	float Height;
	float X;
	float Y;
	CircleCollision enemyCollision;

	void setCircle()
	{
		enemyCollision.radius = 25;
	}
};

Player avatar;
Enemy enemy;

int main(int argc, char* argv[])
{
	Initialise(backgroundWidth, backgroundHeight, false, "Touhou 15.3");

	SetBackgroundColour(SColour(0, 0, 0, 255));

	int Cirno = CreateSprite("./images/Cirno.png", 45, 50, true);
	int Enemy1 = CreateSprite("./images/BlueFairy.png", 45, 50, true);
	int background = CreateSprite("./images/background.png", 800, 800, true);

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
		if (IsKeyDown('P'))
		{
			Bullet bullets;
			bullets.x = avatar.X;
			bullets.y = avatar.Y;

			avatar.AllBullets.push_back(bullets);
		}

		MoveSprite(background, 400, 400);
		DrawSprite(background);

		for (int i = 0; i < avatar.AllBullets.size(); i++)
		{
			float distance = sqrt(pow((avatar.AllBullets[i].x - enemy.X), 2) + pow(avatar.AllBullets[i].y - enemy.Y, 2));
			avatar.AllBullets[i].SetSpeed(avatar.AllBullets[i].xSpeed, avatar.AllBullets[i].ySpeed);
			if (distance < avatar.AllBullets[i].bulletCircle.radius + enemy.enemyCollision.radius)
			{
				std::cout << "hit\n";
			}
		}

		MoveSprite(Cirno, avatar.X, avatar.Y);
		DrawSprite(Cirno);
		MoveSprite(Enemy1, 400, 700);
		DrawSprite(Enemy1);
		ClearScreen();

	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}