// Simulation Wizardry
// UVa ID: 114
// Verdict: Accepted
// Submission Date: 2011-12-02
// UVa Run Time: 0.084s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;
const int GRID = 0, OBSTACLE = 1, WALL = 3;
const int RIGHT = 0, UP = 1, LEFT = 2, DOWN = 3;

struct obstacle
{
	int value, cost;
};

struct ball
{
	int x, y, direction, lifetime, points;
};

ball pinball;
obstacle bumpers[MAXN][MAXN];
int grid[MAXN][MAXN], gridWidth, gridHeight, costHitWall;
int offset[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

void play(void)
{
	int newX, newY;
	while (pinball.lifetime > 0)
	{
		pinball.lifetime--;
		newX = pinball.x + offset[pinball.direction][0];
		newY = pinball.y + offset[pinball.direction][1];

		if (grid[newY][newX] == WALL)
		{
			if (newY == gridHeight && pinball.direction == UP ||
				newY == 1 && pinball.direction == DOWN ||
				newX == gridWidth && pinball.direction == RIGHT ||
				newX == 1 && pinball.direction == LEFT)
			{
				pinball.direction--;
				if (pinball.direction < 0)
					pinball.direction += 4;
				pinball.lifetime -= costHitWall;	
			}			
		}
		else if (grid[newY][newX] == OBSTACLE)
		{
			pinball.direction--;
			if (pinball.direction < 0)
				pinball.direction += 4;
			if (pinball.lifetime > 0)
			{
				pinball.points += bumpers[newY][newX].value;
				pinball.lifetime -= bumpers[newY][newX].cost;
			}
		}
		else
		{
			pinball.x = newX;
			pinball.y = newY;
		}
	}
}

int main (int argc, char *argv[])
{
	int totalPoints = 0, numberBumpers, tmpX, tmpY;

	cin >> gridWidth >> gridHeight;
	cin >> costHitWall;
	for (int i = 1; i <= gridHeight; i++)
		for (int j = 1; j <= gridWidth; j++)
			if (i == 1 || j == 1 || i == gridHeight || j == gridWidth)
				grid[i][j] = WALL;
			else
				grid[i][j] = GRID;

	cin >> numberBumpers;
	for (int i = 1; i <= numberBumpers; i++)
	{
		cin >> tmpX >> tmpY;
		grid[tmpY][tmpX] = OBSTACLE;
		cin >> bumpers[tmpY][tmpX].value;
		cin >> bumpers[tmpY][tmpX].cost;
	}

	while (cin >> pinball.x)
	{
		cin >> pinball.y >> pinball.direction >> pinball.lifetime;
		pinball.points = 0;
		
		play();
	
		totalPoints += pinball.points;
		cout << pinball.points << endl;
	}

	cout << totalPoints << endl;

	return 0;
}
