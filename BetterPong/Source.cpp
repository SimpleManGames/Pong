#include <iostream>
#include <vector>
#include <ctime>
#include "sfwdraw.h"
#include "MyMath.h"
#include "Struct.h"
#include "Random.h"

using namespace sfw;
using namespace str;
using namespace std;

const int screenWidth = 800;
const int screenHeight = 300;

Random RNG;

struct ColRectangle
{
	float x, y, dimX, dimY;

	void drawRect()
	{
		sfw::drawLine(x, y, x + dimX, y);
		sfw::drawLine(x, y, x, y + dimY);
		sfw::drawLine(x, y + dimY, x + dimX, y + dimY);
		sfw::drawLine(x + dimX, y, x + dimX, y + dimY);
	}
	MapSegment getCol(unsigned int i)
	{
		switch (i)
		{
		case 0: return MapSegment::MapSegment(Point{ x, y }, Point{ x + dimX, y });
		case 1: return MapSegment::MapSegment(Point{ x, y }, Point{ x, y + dimY });
		case 2: return MapSegment::MapSegment(Point{ x, y + dimY }, Point{ x + dimX, y + dimY });
		case 3: return MapSegment::MapSegment(Point{ x + dimX, y }, Point{ x + dimX, y + dimY });
		}
	}
};
struct Paddle;
struct Ball
{
	Circle c;
	int speed;
	Point spawnPoint;
	Vector2 currentDirection;

	void updateBall(Paddle &p)
	{
		//Draws ball
		drawCircle(c.P.x, c.P.y, c.R);

		//Moves ball
		c.P.x += currentDirection.x * speed;
		c.P.y += currentDirection.y * speed;

	}
	void resetBall() { c.P.x = spawnPoint.x;  c.P.y = spawnPoint.y; }
};
struct Paddle
{
	ColRectangle r;
	int speed;
	char upChar, downChar;

	int Score;

	MapSegment getPaddle(unsigned int i)
	{
		switch (i)
		{
		case 0: return MapSegment::MapSegment(Point{ r.x, r.y }, Point{ r.x + r.dimX, r.y });
		case 1: return MapSegment::MapSegment(Point{ r.x, r.y }, Point{ r.x, r.y + r.dimY });
		case 2: return MapSegment::MapSegment(Point{ r.x, r.y + r.dimY }, Point{ r.x + r.dimX, r.y + r.dimY });
		case 3: return MapSegment::MapSegment(Point{ r.x + r.dimX, r.y }, Point{ r.x + r.dimX, r.y + r.dimY });
		}
	}

	void Update(vector<MapSegment> &mapS, Ball &b)
	{
		// Draws Paddles
		for (int i = 0; i < 2; ++i) { r.drawRect(); }

		// Updates Movement
		int moved = 0;
		if (getKey(upChar))		   { r.y -= speed * getDeltaTime(); moved = -1; }
		else if (getKey(downChar)) { r.y += speed * getDeltaTime(); moved = 1; }

		// Checks Collision
		bool collided = false;
		for (int m = 0; m < mapS.size(); m++) { for (int p = 1; p < 4; p++) { if (mapSegCol(mapS[m], getPaddle(p))) { collided = true; } } }
		if (collided)
		{
			if (moved == -1) r.y += speed * getDeltaTime();
			if (moved == 1) r.y -= speed * getDeltaTime();
		}
		bool ballcol = false;
		if (b.c.P.x - b.c.R < r.x + r.dimX &&
			b.c.P.x + b.c.R > r.x &&
			b.c.P.y - b.c.R > r.y + r.dimY &&
			b.c.P.y + b.c.R < r.y - r.dimY)
		{
			ballcol = true;
		}
		cout << ballcol << endl;
	}
};

struct Wall
{
	Point p1, p2;

	void spawnWall(vector<MapSegment> &w)
	{
		w.push_back(MapSegment::MapSegment(p1, p2));
		drawLine(p1.x, p1.y, p2.x, p2.y);
	}
	MapSegment getWall(unsigned int i)
	{
		switch (i)
		{
		case 0: return MapSegment::MapSegment({ { 0, 0 }, { screenWidth / 2, 0 } });
		case 1: return MapSegment::MapSegment({ { screenWidth / 2, 0 },{ screenWidth, 0 } });
		case 2: return MapSegment::MapSegment({ { 0, screenHeight }, { screenWidth / 2, screenHeight } });
		case 3:	return MapSegment::MapSegment({ { screenWidth / 2, screenHeight },{ screenWidth, screenHeight } });

		case 8: return MapSegment::MapSegment({ { 0, 0 }, { screenWidth, 0} });
		case 9: return MapSegment::MapSegment({ {0, screenHeight }, { screenWidth, screenHeight } });
		}
	}
	void checkCollision(Ball &b)
	{
		cout << b.speed << endl;
		if (b.c.P.y - b.c.R <= 0 && b.currentDirection.y < 1)
		{
			cout << "Above" << endl;
			b.c.P.y += 2;
			b.currentDirection.y = -1 * (b.currentDirection.y);
		}
		if (b.c.P.y + b.c.R >= screenHeight && b.currentDirection.y > -1)
		{
			cout << "Below" << endl;
			b.c.P.y -= 2;
			b.currentDirection.y = -1 * b.currentDirection.y;
		}
	}
};

int main()
{
	initContext(screenWidth, screenHeight, "Pong!");

	Paddle p1 = { { 25, (screenHeight / 2) - 25, 25, 100 }, 100, 'W', 'S', 0 };
	Paddle p2 = { { screenWidth - 50, (screenHeight / 2) - 25, 25, 100 }, 100, 'O', 'L', 0 };

	Wall wA[5] = {};
	wA[1] = { { 0, 0 }, { screenWidth / 2, 0 } };
	wA[2] = { { screenWidth / 2, 0 }, { screenWidth, 0 } };
	wA[3] = { { 0, screenHeight }, { screenWidth / 2, screenHeight } };
	wA[4] = { { screenWidth / 2, screenHeight }, { screenWidth, screenHeight / 2 } };
	vector<MapSegment> w;

	Ball b = { { { (screenWidth / 2) - 5, (screenHeight / 2) - 5 }, 10 }, // Circle
				 5, // Speed    
				 { (screenWidth / 2) - 5, (screenHeight / 2) - 5 }, // SpawnPoint
				 { (2 * (float)RNG.NextDouble() - 1), (2 * (float)RNG.NextDouble() - 1) } }; // Current Direction

	while (stepContext())
	{
		// Updates the paddles
		p1.Update(w, b);
		p2.Update(w, b);
		//Draws the walls
		for (int i = 0; i < 4; ++i) { wA[i].spawnWall(w); wA[i].checkCollision(b); }
		b.updateBall(p1);
	}
	termContext();
}
