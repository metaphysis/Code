// UVa Problem 118 - Mutant Flatworld Explorers
// Verdict: Accepted
// Submission Date: 2011-11-26
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 网格，数据结构，模拟。若某次机器人在此位置落到边界之外，则下一个机器人在此位置，
// 若有指令导致该机器人走出边界，则忽略该条指令，直到处理完毕指令。

#include <iostream>

using namespace std;

#define MAXN 55

#define DANGEROUS 0
#define SAFE 1

struct status
{
	int x, y;
	string direction;
};

int grid[MAXN][MAXN], width, height;

bool move(status & s, string instructions)
{
	status last;
	for (int i = 0; i < instructions.length(); i++)
	{
		// 稍显华丽的  if else。
		last = s;
		if (s.direction == "N" && instructions[i] == 'L')
			s.direction = "W";
		else if (s.direction == "N" && instructions[i] == 'R')
			s.direction = "E";
		else if (s.direction == "N" && instructions[i] == 'F')
			s.y += 1;
		else if (s.direction == "S" && instructions[i] == 'L')
			s.direction = "E";
		else if (s.direction == "S" && instructions[i] == 'R')
			s.direction = "W";
		else if (s.direction == "S" && instructions[i] == 'F')
			s.y -= 1;
		else if (s.direction == "W" && instructions[i] == 'L')
			s.direction = "S";
		else if (s.direction == "W" && instructions[i] == 'R')
			s.direction = "N";
		else if (s.direction == "W" && instructions[i] == 'F')
			s.x -= 1;
		else if (s.direction == "E" && instructions[i] == 'L')
			s.direction = "N";
		else if (s.direction == "E" && instructions[i] == 'R')
			s.direction = "S";
		else if (s.direction == "E" && instructions[i] == 'F')
			s.x += 1;

		if (s.x > width || s.x < 0 || s.y > height || s.y < 0)
		{
			if (grid[last.y][last.x] == DANGEROUS)
				s = last;
			else
			{
				cout << last.x << " " << last.y << " " << last.
					direction;
				cout << " LOST" << endl;
				grid[last.y][last.x] = DANGEROUS;
				return true;
			}
		}
	}

	cout << s.x << " " << s.y << " " << s.direction << endl;

	return false;
}

int main(int argc, char const *argv[])
{
	status robot;
	string line;

	cin >> width >> height;
	for (int i = 0; i <= height; i++)
		for (int j = 0; j <= width; j++)
			grid[i][j] = SAFE;

	while (cin >> robot.x >> robot.y >> robot.direction)
	{
		cin >> line;
		move(robot, line);
	}

	return 0;
}
