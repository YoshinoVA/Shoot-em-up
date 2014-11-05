#include "AIE.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <vector>

int backgroundWidth = 800;
int backgroundHeight = 800;

enum Gamestates
{
	Game,
	Main,
	HowTo,
	Win,
	Lose,
};

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

	bool isAlive = false;

	void SetSpeed(float x_BulletSpeed, float y_BulletSpeed)
	{
		x += x_BulletSpeed;
		y += y_BulletSpeed;
		MoveSprite(iSpriteID, x, y);
		DrawSprite(iSpriteID);
		if (y > backgroundHeight)
		{
			isAlive = false;
		}
		if (y > backgroundWidth)
		{
			isAlive = false;
		}
	}
	void move(float aDelta)
	{
		if (isAlive)
		{
			x += xSpeed * aDelta;
			y += ySpeed * aDelta;
		}
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

	bool isAlive = true;

	std::vector<Bullet*> AllBullets;

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
	float charaX = 400;
	float charaY = 700;
	float xSpeed = 10;
	float ySpeed = 100;
	CircleCollision enemyCollision;

	void setCircle()
	{
		enemyCollision.radius = 25;
	}
	bool isAlive = true;

	void Draw()
	{
		if (isAlive)
		{
			MoveSprite(iSpriteID, charaX, charaY);
			DrawSprite(iSpriteID);
		}
	}
	void move(float a_Delta)
	{
		charaX -= xSpeed * a_Delta;
		charaY -= ySpeed * a_Delta;
	}
	void SetSpeed(float x_EnemySpeed, float y_EnemySpeed)
	{
		charaX -= x_EnemySpeed;
		charaX -= y_EnemySpeed;
	}
};

Player avatar;
Enemy enemy;
Enemy enemy2;

int Score = 0;
char ScoreText[5];

int main(int argc, char* argv[])
{
	Initialise(backgroundWidth, backgroundHeight, false, "Touhou 15.4683");

	SetBackgroundColour(SColour(0, 0, 0, 255));

	int Cirno = CreateSprite("./images/Cirno.png", 45, 50, true);
	int Enemy1 = CreateSprite("./images/BlueFairy.png", 45, 50, true);
	int Enemy2 = CreateSprite("./images/YellowFairy.png", 45, 50, true);
	enemy.iSpriteID = Enemy1;
	enemy2.iSpriteID = Enemy2;
	int background = CreateSprite("./images/background.png", 800, 800, true);
	int Cover = CreateSprite("./images/GameCover.png", 800, 800, true);
	int HowToCover = CreateSprite("./images/HowToCover.png", 800, 800, true);
	int LoseScreen = CreateSprite("./images/LoseScreen.png", 800, 800, true);
	int WinScreen = CreateSprite("./images/WinScreen.png", 800, 800, true);

	for (int j = 0; j < 100; j++)
	{
		Bullet* bill = new Bullet();
		avatar.AllBullets.push_back(bill);
	}

	float deltaTime;
	Gamestates CurrentState = Main;
	//Game Loop 
	do
	{
			switch (CurrentState)
			{
			case Main:
			{
				MoveSprite(Cover, 400, 400);
				DrawSprite(Cover);

				if (IsKeyDown('Y'))
				{
					CurrentState = Game;
				}
				if (IsKeyDown('M'))
				{
					CurrentState = HowTo;
				}
				break;
			}
			case HowTo:
			{
				MoveSprite(HowToCover, 400, 400);
				DrawSprite(HowToCover);
				if (IsKeyDown(' '))
				{
					CurrentState = Main;
				}
				break;
			}
			case Game:
			{
				deltaTime = GetDeltaTime();
				enemy2.xSpeed = -10;
				//move character and shoot
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

					for (int i = 0; i < avatar.AllBullets.size(); i++)
					{
						if (avatar.AllBullets[i]->isAlive == false)
						{
							avatar.AllBullets[i]->isAlive = true;
							avatar.AllBullets[i]->x = avatar.X;
							avatar.AllBullets[i]->y = avatar.Y;
							break;
						}
					}
				}
				// ENEMY 1
				if (enemy.charaY < 0)
				{
					enemy.isAlive = false;
				}
				if (enemy.isAlive == false)
				{
					enemy.charaX = 400;
					enemy.charaY = 800;
					enemy.isAlive = true;
				}
				// ENEMY 2
				if (enemy2.charaY < 0)
				{
					enemy2.isAlive = false;
				}
				if (enemy2.isAlive == false)
				{
					enemy2.charaX = 500;
					enemy2.charaY = 800;
					enemy2.isAlive = true;
				}

				// BACKGROUND
				MoveSprite(background, 400, 400);
				DrawSprite(background);

				avatar.setCircle();
				enemy2.setCircle();
				for (int i = 0; i < avatar.AllBullets.size(); i++)
				{
					float distance = sqrt(pow((avatar.AllBullets[i]->x - enemy.charaX), 2) + pow(avatar.AllBullets[i]->y - enemy.charaY, 2));
					avatar.AllBullets[i]->SetSpeed(avatar.AllBullets[i]->xSpeed, avatar.AllBullets[i]->ySpeed);
					if (distance < avatar.AllBullets[i]->bulletCircle.radius + enemy.enemyCollision.radius)
					{
						enemy.isAlive = false;
						Score++;
						itoa(Score, ScoreText, 10);
					}
				}
				for (int i = 0; i < avatar.AllBullets.size(); i++)
				{
					float distance = sqrt(pow((avatar.AllBullets[i]->x - enemy2.charaX), 2) + pow(avatar.AllBullets[i]->y - enemy2.charaY, 2));
					avatar.AllBullets[i]->SetSpeed(avatar.AllBullets[i]->xSpeed, avatar.AllBullets[i]->ySpeed);
					if (distance < avatar.AllBullets[i]->bulletCircle.radius + enemy2.enemyCollision.radius)
					{
						enemy2.isAlive = false;
						Score++;
						itoa(Score, ScoreText, 10);
					}
				}

				float distance2 = sqrt(pow((enemy2.charaX - avatar.X), 2) + pow(enemy2.charaY - avatar.Y, 2));
				if (distance2 < enemy2.enemyCollision.radius + avatar.playerCollision.radius)
				{
					avatar.isAlive = false;
				}
				float distance = sqrt(pow((enemy.charaX - avatar.X), 2) + pow(enemy.charaY - avatar.Y, 2));
				if (distance < enemy.enemyCollision.radius + avatar.playerCollision.radius)
				{
					avatar.isAlive = false;
				}

				MoveSprite(Cirno, avatar.X, avatar.Y);
				DrawSprite(Cirno);
				enemy.move(deltaTime);
				enemy2.move(deltaTime);
				enemy.Draw();
				enemy2.Draw();
				DrawString(ScoreText, backgroundWidth * .025f, backgroundHeight - 2);
				if (Score == 1000)
				{
					CurrentState = Win;
				}
				if (avatar.isAlive == false)
				{
					CurrentState = Lose;
				}
				break;
			}
			case Win:
			{
				MoveSprite(WinScreen, 400, 400);
				DrawSprite(WinScreen);

				if (IsKeyDown(' '))
				{
					CurrentState = Main;
				}
				break;
			}
			case Lose:
			{
				MoveSprite(LoseScreen, 400, 400);
				DrawSprite(LoseScreen);

				if (IsKeyDown(' '))
				{
					CurrentState = Main;
				}
				break;
			}

				ClearScreen();
			}
	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}