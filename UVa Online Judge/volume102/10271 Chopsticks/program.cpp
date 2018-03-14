// Chopsticks （筷子）
// PC/UVa IDs: 111107/10271, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-18
// UVa Run Time: 0.100s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 设 badness[i][j] 为取前 j 支筷子形成的 i 组筷子组合所能得到的最小难用度，length[j] 为第
// j 根筷子的长度，则有以下状态转移方程：
//
// badness[i][j] = min{badness[i][j - 1], badness[i - 1][j - 2] + (length[j] -
// length[j - 1]) * (length[j] - length[j - 1) | j >= 3 * i - 1}
//
// 对于筷子长度形成的序列（按递增排序）：
//
// ...，C1，C2，C3，...
//
// 可以证明，若 C1 < C2，则最优方案中若 C1 被用作第一支筷子，则 C2 必被用作为第二支筷子。可使用
// 反证法证明。假设最优方案中 C1 未与 C2 组成一组筷子，则由于 C1 与 C2 组成的筷子难用度比 C1
// 与其他筷子组成的筷子难用度都要小，与最优方案相矛盾。故在选择第一支和第二支筷子时，总是选择相邻
// 筷子进行组合，可以获得最小的难用度。

#include <bits/stdc++.h>

using namespace std;

#define MAXN 5001

int length[MAXN];
int badness[MAXN];
int difference[MAXN];
int nGuests, nChopsticks;

// 使用一维数组优化空间使用。
int dynamic_programming()
{
	for (int i = 0; i <= nChopsticks; i++)
		badness[i] = 0;

	for (int i = 1; i <= nGuests; i++)
	{
		int setted = nChopsticks - 3 * (nGuests - i);
		for (int j = setted - 1; j >= 2 * i; j--)
			badness[j] = badness[j - 2] + difference[j];
			
		for (int j = 2 * i + 1; j <= setted - 1; j++)
			badness[j] = min(badness[j], badness[j - 1]);

		badness[setted] = badness[setted - 1];
	}
	
	cout << badness[nChopsticks] << endl;
}

int main(int ac, char *av[])
{
	int cases;
	
	cin >> cases;
	while (cases--)
	{
		cin >> nGuests >> nChopsticks;
		nGuests += 8;

		for (int i = 1; i <= nChopsticks; i++)
		{
			cin >> length[i];
			difference[i] = length[i] - length[i - 1];
			difference[i] *= difference[i];
		}

		dynamic_programming();
	}
}
