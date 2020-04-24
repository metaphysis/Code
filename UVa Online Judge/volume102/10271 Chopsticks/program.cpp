// Chopsticks （筷子）
// PC/UVa IDs: 111107/10271, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2020-04-22
// UVa Run Time: 0.080s
//
// 版权所有（C）2011-2020，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 令 badness[i][j] 为取前 j 支筷子形成的 i 组筷子组合所能得到的最小难用度，L[j] 为第
// j 根筷子的长度，则有以下状态转移方程：
//
// badness[i][j] = min{badness[i][j - 1], badness[i - 1][j - 2] + (L[j] -
// L[j - 1]) * (L[j] - L[j - 1) | j >= 3 * i}
//
// 对于筷子长度形成的序列（按非递减排序）：
//
// ...，C1，C2，C3，...
//
// 可以证明，若 C1 <= C2，则最优方案中若 C1 被用作第一支筷子，则 C2 必被用作为第二支筷子。可使用
// 反证法证明。假设最优方案中 C1 未与 C2 组成一组筷子，则由于 C1 与 C2 组成的筷子难用度比 C1
// 与其他筷子组成的筷子难用度都要小，与最优方案相矛盾。故在选择第一支和第二支筷子时，总是选择相邻
// 筷子进行组合，可以获得最小的难用度。注意，在进行动态规划时，需要将筷子的长度按不递增的顺序排列，
// 这样才能保证动态规划的正确性。

#include <bits/stdc++.h>

using namespace std;

int L[5010] = {0};
int badness[1010][5010] = {0};
int nGuests, nChopsticks;

int getBadness(int i)
{
    return (L[i] - L[i - 1]) * (L[i] - L[i - 1]);
}

int main(int ac, char *av[])
{
	int cases;
	
	cin >> cases;
	while (cases--)
	{
		cin >> nGuests >> nChopsticks;
		nGuests += 8;
		for (int i = 1; i <= nChopsticks; i++) cin >> L[i];		    
        sort(L + 1, L + nChopsticks + 1, greater<int>());
		for (int i = 1; i <= nGuests; i++)
		{
		    badness[i][i * 3] = badness[i - 1][i * 3 - 2] + getBadness(i * 3);
		    for (int j = i * 3 + 1; j <= nChopsticks; j++)
		        badness[i][j] = min(badness[i][j - 1], badness[i - 1][j - 2] + getBadness(j));
		}
		cout << badness[nGuests][nChopsticks] << '\n';
	}
}
