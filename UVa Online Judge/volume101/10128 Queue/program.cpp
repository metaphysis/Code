// Queue （队伍）
// PC/UVa IDs: 110803/10128, Popularity: B, Success rate: high Level: 2
// Verdict: Accepted 
// Submission Date: 2011-07-08
// UVa Run Time: 0.040s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 回溯法明显是太慢，效率不可接受，虽然本题归于回溯法一节，但是用回溯的方法效率太低（被
// Programming Challenges 误导了）。可以考虑动态规划。动态规划可以这样考虑：假设当前已有 n 个
// 人排列成队伍，新增的人是最矮的，则可以得到以下关系：
//
// perm[n][p][r] = perm[n - 1][p][r] * (n - 2) + perm[n - 1][p - 1][r] +
// perm[n - 1][p][r - 1]
//
// （1）perm[n - 1][p][r] * (n - 2)：新增最矮的人可以放在排列好的 n - 1 个人形成的左边刚好
//     p 人，右边刚好 r 人视野不被挡住的队列的中间，因为有 n - 2 个空，所以共有 perm[n - 1]
//     [p][r] * (n - 2) 种安排方法。
//
// （2）perm[n - 1][p - 1][r]：由于该人比所有人矮，故可以直接放在队首。
//
// （3）perm[n - 1][p][r - 1]：由于该人比所有人矮，故可以直接放在队尾。

#include <bits/stdc++.h>

using namespace std;

#define NMAX 14

long long perm[NMAX][NMAX][NMAX];	// 解空间。
long long solution_counter;	// 解的个数。

// 判读该排列是否符合条件。
bool check(int number[], int n, int p, int r)
{
	int tp, tr, left, right;

	tp = tr = 1;

	left = number[0];
	right = number[n - 1];

	for (int i = 1, j = n - 2; i <= n - 1 && j >= 0; i++, j--)
	{
		if (left < number[i])
		{
			tp++;
			left = number[i];
		}
		if (right < number[j])
		{
			tr++;
			right = number[j];
		}
	}

	return tp == p && tr == r;
}

// 构建排列的候选元素。
void construct_candidates(int number[], int k, int n, int c[], int *ncandidates)
{
	bool in_perm[NMAX];

	memset(in_perm, false, sizeof(in_perm));
	for (int i = 0; i < k; i++)
		in_perm[number[i] - 1] = true;

	*ncandidates = 0;
	for (int i = 1; i <= n; i++)
		if (in_perm[i - 1] == false)
			c[(*ncandidates)++] = i;
}

// 回溯法构建所有排列。
void backtract(int number[], int k, int n, int p, int r)
{
	int c[NMAX];
	int candidates;

	if (k == n)
	{
		if (check(number, n, p, r))
			solution_counter++;
	}
	else
	{
		construct_candidates(number, k, n, c, &candidates);
		for (int i = 0; i < candidates; i++)
		{
			number[k] = c[i];
			backtract(number, k + 1, n, p, r);
		}
	}
}

// 回溯法解题，效率低，可考虑先将解空间表示成数组，然后根据具体数据直接输出结果。
long long permutation(int n, int p, int r)
{
	int number[NMAX];

	solution_counter = 0;
	backtract(number, 0, n, p, r);

	return solution_counter;
}

// 动态规划，实际上是自下而上计算总方案数。
long long dynamic_programming(void)
{
	perm[1][1][1] = 1;

	for (int n = 2; n < NMAX; n++)
		for (int p = 1; p < NMAX; p++)
			for (int r = 1; r < NMAX; r++)
				perm[n][p][r] =
					perm[n - 1][p][r] * (n - 2) + 
				perm[n - 1][p - 1][r] + perm[n - 1][p][r - 1];
}

int main(int ac, char *av[])
{
	int t, n, p, r;

	// 动态规划解题。
	dynamic_programming();

	// 循环读入测试数据直到结束。
	cin >> t;
	while (t--)
	{
		// 读入数据，计算满足条件的组合。输出。
		cin >> n >> p >> r;
		cout << perm[n][p][r] << endl;
	}

	return 0;
}
