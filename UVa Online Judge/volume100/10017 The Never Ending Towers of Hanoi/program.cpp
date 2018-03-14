// UVa Problem 10017 - The Never Ending Towers of Hanoi
// Verdict: Accepted
// Submission Date: 2011-11-17
// UVa Run Time: 0.048s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 经典汉诺塔问题的一个变形吧，加了显示当前柱子圆盘状态的要求。题解使用 bool 数组
// 来表示圆盘是否在某根柱子上，因为有小圆盘总是在大圆盘上面的限制，只需记录某根柱子
// 有哪些圆盘，在输出时，按从大到小的顺序输出圆盘序号即可。

#include <bits/stdc++.h>

using namespace std;

#define A 1
#define B 2
#define C 3

#define MAXDISKS 251
#define MAXPEGS 4

int nDisks, nLastMove, steps;
bool pegs[MAXPEGS][MAXDISKS], stepsReached;

// 显示柱子的圆盘状态。
void printStatus()
{
	if (steps > nLastMove)
	{
		stepsReached = true;
		return;
	}

	for (int i = A; i <= C; i++)
	{
		cout << (char) ('A' + i - 1) << "=>";

		bool printSpace = false;
		for (int j = nDisks; j >= 1; j--)
			if (pegs[i][j])
			{
				if (printSpace == false)
				{
					cout << "  ";
					printSpace = true;
				}

				cout << " " << j;
			}

		cout << "\n";
	}

	cout << "\n";

	steps++;
}

// 移动圆盘并显示。
void move(int n, int from, int middle, int to)
{
	pegs[from][n] = false;
	pegs[to][n] = true;

	printStatus();
}

// 递归实现汉诺塔移动。
void hanoi(int n, int from, int middle, int to)
{
	if (stepsReached)
		return;

	if (n == 1)
	{
		move(n, from, middle, to);
		return;
	}
	else
	{
		hanoi(n - 1, from, to, middle);
		move(n, from, middle, to);
		hanoi(n - 1, middle, from, to);
	}
}

int main(int argc, char const *argv[])
{
	int cases = 1;

	while (cin >> nDisks >> nLastMove, nDisks || nLastMove)
	{
		cout << "Problem #" << cases++ << "\n\n";

		steps = 0;
		stepsReached = false;

		for (int i = 1; i < MAXPEGS; i++)
			for (int j = 1; j <= nDisks; j++)
				pegs[i][j] = false;
		for (int i = 1; i <= nDisks; i++)
			pegs[1][i] = true;

		printStatus();

		hanoi(nDisks, A, B, C);
	}

	return 0;
}
