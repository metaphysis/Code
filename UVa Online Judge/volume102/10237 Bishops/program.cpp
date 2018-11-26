// Bishops
// Verdict: Accepted 
// Submission Date: 2018-11-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;

long long bishops_by_combinatorics(int n, int k)
{
	// 假设棋盘左上角第一个格子为白色格子。
	long long white[32];
	long long black[32];
	
	// 得到每一列白色格子的数目。格子数按从小到大排列。
	for (int i = 1; i <= n; i++)
		white[i] = ((i % 2) ? i : white[i - 1]);
	// 得到每一列黑色格子的数目。格子数按从小到大排列。
	for (int i = 1; i <= n - 1; i++)
		black[i] = ((i % 2) ? (i + 1) : black[i - 1]);
	
	// 存储前 i 列放置 j 个象的方法。白色格子和黑色格子的放置方法数分别计算。
	// 因为给定最多 8 * 8 的棋盘，则最大能放置象的数目为 14 个。	
	long long white_solutions[32][64] = { {0} };
	long long black_solutions[32][64] = { {0} };
	// 初始化边界条件。
	for (int i = 0; i <= n; i++)
		white_solutions[i][0] = 1;
	for (int j = 1; j <= k; j++)
		white_solutions[0][j] = 0;
	// 根据递推公式计算白色格子放置方案数。
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k && j <= i; j++)
			white_solutions[i][j] =
				white_solutions[i - 1][j] + 
				white_solutions[i - 1][j - 1] * (white[i] - j + 1);
	// 初始化边界条件。
	for (int i = 0; i <= n - 1; i++)
		black_solutions[i][0] = 1;
	for (int j = 1; j <= k; j++)
		black_solutions[0][j] = 0;
	// 根据递推公式计算黑色格子放置方案数。
	for (int i = 1; i <= n - 1; i++)
		for (int j = 1; j <= k && j <= i; j++)
			black_solutions[i][j] =
				black_solutions[i - 1][j] + 
				black_solutions[i - 1][j - 1] * (black[i] - j + 1);
	
	// 统计总的放置方案数。根据乘法原理和加法原理，总的方案数等于 n * n 的棋盘
	// n 行白色格子放置 0 个象的方案乘以 n - 1 行黑色格子放置 k 个象的方案数，
	// 加上 n 行白色格子放置 1 个象的方案乘以 n - 1 行黑色格子放置 k - 1 个
	// 象的方案数，加上 n 行白色格子放置 2 个象的方案乘以 n - 1 行黑色格子放
	// 置 k - 2 个象的方案数......
	long long total = 0;
	for (int i = 0; i <= k; i++)
		total += white_solutions[n][i] * black_solutions[n - 1][k - i];
	return total;
}
	
long long bishops(int n, int k)
{
	// 处理特殊情况的解。
	// k == 0，即棋盘上不放置象，只有一种方法。
	if (k == 0)
		return 1LL;
	
	// 当棋盘为 1 * 1 时，最多只能放置放置 1 个象。
	if (n == 1)
		return k;
	
	// 当 n >= 2 时，由分析可知，最多只能放置 2 * (n - 1) 个象。
	// 当大于 2 * (n - 1) 时无解。
	if (k > 2 * (n - 1))
		return 0LL;
	
	// 一般情况的解。
	//return little_bishops_by_backtracking(n, k);
	return bishops_by_combinatorics(n, k);
}
	
int main(int argc, char *argv[])
{
	int n, k;
	
	while (cin >> n >> k, n || k)
		cout << bishops(n, k) << '\n';
	
	return 0;
}
