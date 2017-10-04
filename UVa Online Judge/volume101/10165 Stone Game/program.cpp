// UVa Problem 10165 - Stone Game
// Verdict: Accepted
// Submission Date: 2011-11-17
// UVa Run Time: 0.020s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 啊哈，很有趣的一个题目。在网络上搜索一下 Nim 和 Xor，就可以了解到相关信息。若是自己想，一年也
// 想不出来吧。

#include <iostream>

using namespace std;

int main (int argc, char const* argv[])
{
	int piles, stones, tmpStones;

	while (cin >> piles, piles)
	{
		stones = 0;
		for (int i = 1; i <= piles; i++)
		{
			cin >> tmpStones;
			stones ^= tmpStones;
		}

		cout << (stones ? "Yes" : "No") << endl;
	}

	return 0;
}

