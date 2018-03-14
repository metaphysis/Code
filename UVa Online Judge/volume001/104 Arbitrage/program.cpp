// Arbitrage
// UVa ID: 104
// Verdict: Accepted
// Submission Date: 2011-12-22
// UVa Run Time: 0.068s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 本质是求一个最小环，要求边权的积大于或等于 1.02，可以使用动态规划和 Floyd-Warshall
// 算法（实际上 Floyd-Warshall 本身就已经使用了动态规划的思想）来解决本题。
//
// 用 profit(i, j, step) 表示 “由 i 经过 step 步套汇得到 j 可以得到的最大 profit 值”。
// 则有以下递推关系：
//
// profit(i, j, step) = profit(i, k, step-1) * profit(k, j, 1)
// 条件是：profit(i, k, step-1) * profit(k, j, 1) > profit(i, j, step)
// 递推初始值：profit(i, i, 1) = 1.0

#include <bits/stdc++.h>

using namespace std;

#define MAXN 20

double profit[MAXN + 1][MAXN + 1][MAXN + 1];
int memo[MAXN + 1][MAXN + 1][MAXN + 1];
int n;

void output(int start, int end, int step)
{
	if (step >= 2)
	{
		output(start, memo[start][end][step], step - 1);
		cout << " " << memo[start][end][step];
	}
}

int main(int argc, char *argv[])
{
	while (cin >> n)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					profit[i][j][k] = 0.0;

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i == j)
				{
					profit[i][j][1] = 1;
					memo[i][j][1] = i;
				}
				else
				{
					cin >> profit[i][j][1];
					memo[i][j][1] = i;
				}

		int start, steps;
		bool arbitrage = false;

		for (int step = 2; step <= n; step++)
			for (int k = 1; k <= n; k++)
				for (int i = 1; i <= n; i++)
					for (int j = 1; j <= n; j++)
					{
						double temp = profit[i][k][step - 1] * profit[k][j][1];
						if (temp > profit[i][j][step])
						{
							profit[i][j][step] = temp;
							memo[i][j][step] = k;

							if (i == j && profit[i][j][step] > 1.01)
							{
								arbitrage = true;
								start = i;
								steps = step;
								goto out;
							}
						}
					}

out:
		if (arbitrage)
		{
			cout << start;
			output(start, start, steps);
			cout << " " << start << endl;		
		}
		else
			cout << "no arbitrage sequence exists" << endl;
	}

	return 0;
}
