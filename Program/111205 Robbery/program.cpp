// Robbery （抢劫）
// PC/UVa IDs: 111205/707, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-11-04
// UVa Run Time: 0.036s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 提示：如何建图来同时刻画时间和空间？如何高效的遍历以确定可能的位置？如果解决了这两个问题，本问
// 题就解决了！

#include <iostream>

using namespace std;

#define MAXN 100

#define UNOBSERVED 0
#define OBSERVED 1
#define REACHABLE 2
#define I_AM_HERE 3

int width, height, timeLocked;
int grid[MAXN + 1][MAXN + 1][MAXN + 1];
int offset[5][2] = { { 0, 0 }, { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };

// 先从最后时刻往前搜索，找到可以到达的位置，标记。
void backward_dfs(int time, int y, int x)
{
	if (time == 1)
	{
		grid[time][y][x] = REACHABLE;
		return;
	}

	for (int i = 0; i < 5; i++)
	{
		int tmpY = y + offset[i][0];
		int tmpX = x + offset[i][1];

		if (1 <= tmpY && tmpY <= height && 1 <= tmpX && tmpX <= width)
			if (grid[time - 1][tmpY][tmpX] == UNOBSERVED)
			{
				grid[time][y][x] = REACHABLE;
				backward_dfs(time - 1, tmpY, tmpX);
			}
			else if (grid[time - 1][tmpY][tmpX] == REACHABLE)
				grid[time][y][x] = REACHABLE;
	}
}

// 从前往后搜索，将可能的位置标记。
void forward_dfs(int time, int y, int x)
{
	if (time == timeLocked)
	{
		grid[time][y][x] = I_AM_HERE;
		return;
	}

	for (int i = 0; i < 5; i++)
	{
		int tmpY = y + offset[i][0];
		int tmpX = x + offset[i][1];
		
		if (1 <= tmpY && tmpY <= height && 1 <= tmpX && tmpX <= width)
			if (grid[time + 1][tmpY][tmpX] == REACHABLE)
			{
				grid[time][y][x] = I_AM_HERE;
				forward_dfs(time + 1, tmpY, tmpX);
			}
			else if (grid[time + 1][tmpY][tmpX] == I_AM_HERE)
				grid[time][y][x] = I_AM_HERE;
	}
}

int main(int ac, char *av[])
{
	int cases = 1;
	int messages;
	int current, left, top, right, bottom;

	while (cin >> width >> height >> timeLocked, width || height || timeLocked)
	{
		cout << "Robbery #" << cases++ << ":\n";

		for (int t = 1; t <= timeLocked; t++)
			for (int y = 1; y <= height; y++)
				for (int x = 1; x <= width; x++)
					grid[t][y][x] = UNOBSERVED;
		
		// 读取各时间片的封锁范围，劫匪在该时刻不会在此范围内。
		cin >> messages;
		for (int i = 1; i <= messages; i++)
		{
			cin >> current >> left >> top >> right >> bottom;

			for (int y = top; y <= bottom; y++)
				for (int x = left; x <= right; x++)
					grid[current][y][x] = OBSERVED;
		}

		// 从最后一个时间片往前进行深度优先遍历。假设在时刻 t，劫匪在位置（width，
		// height），则在上一时刻 t - 1，劫匪只可能在（width - 1，height），
		// （width + 1，height），（width，height - 1），（width，height + 1）
		// （width，height）五个位置中的一个。注意需要经过正反两个方向的搜索才能确定
		// 通路上的可能位置。
		for (int y = 1; y <= height; y++)
			for (int x = 1; x <= width; x++)
				if (grid[timeLocked][y][x] == UNOBSERVED)
					backward_dfs(timeLocked, y, x);

		// 正向搜索以确定确实可行的位置。
		for (int y = 1; y <= height; y++)
			for (int x = 1; x <= width; x++)
				if (grid[1][y][x] == REACHABLE)
					forward_dfs(1, y, x);

		// 根据各个时间片可能位置的数量决定输出。
		bool nothing = true;
		pair < int, int > location;
		for (int t = 1; t <= timeLocked; t++)
		{
			int exactLocation = 0;
			for (int y = 1; y <= height; y++)
			{
				for (int x = 1; x <= width; x++)
					if (grid[t][y][x] == I_AM_HERE)
					{
						exactLocation++;
						location = make_pair(x, y);
						if (exactLocation > 1)
							break;
					}

				if (exactLocation > 1)
					break;
			}

			if (exactLocation == 0)
			{
				cout << "The robber has escaped.\n";
				nothing = false;
				break;
			}

			if (exactLocation == 1)
			{
				cout << "Time step " << t << ": ";
				cout << "The robber has been at ";
				cout << location.first << "," << location.second;
				cout << ".\n";
				nothing = false;
			}
		}

		if (nothing)
			cout << "Nothing known.\n";

		cout << "\n";
	}

	return 0;
}
