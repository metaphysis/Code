// UVa Problem 108 - Maximum Sum
// Verdict: Accepted
// Submission Date: 2011-11-23
// UVa Run Time: 0.112s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 该题可以归结为网格上的算法。实际上可以通过正交范围查询来解决，若是用嵌套循环来
// 求矩形内元素和，难免 TLE。可以参考《挑战编程：程序设计竞赛训练手册》第十四章第
// 五节的内容。

#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

#define MAXN 110

int grid[MAXN][MAXN], dominance[MAXN][MAXN], n;

int main (int argc, char const* argv[])
{
	// time_t start = clock();

	while (cin >> n)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> grid[i][j];
		
		// 行优先建立优势矩阵。
		memset(dominance, 0, sizeof(dominance));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				dominance[i][j] += grid[i][j];
				if (i > 0)
					dominance[i][j] += dominance[i - 1][j];				
				if (j > 0)
					dominance[i][j] += dominance[i][j - 1];
				if (i > 0 && j > 0)
					dominance[i][j] -= dominance[i - 1][j - 1];
			}

		// 利用正交范围查询找最大和。
		int maxSum = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = i; k < n; k++)
					for (int l = j; l < n; l++)
					{
						int tmpSum = dominance[k][l];
						if (i > 0)
							tmpSum -= dominance[i - 1][l];
						if (j > 0)
							tmpSum -= dominance[k][j - 1];
						if (i > 0 && j > 0)
							tmpSum += dominance[i - 1][j - 1];
						maxSum = max(maxSum, tmpSum);
					}
					
		cout << maxSum << endl;
	}

	// cout << (clock() - start) << endl;

	return 0;
}

