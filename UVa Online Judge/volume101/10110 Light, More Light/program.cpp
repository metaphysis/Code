// Light, More Light （开灯与关灯）
// PC/UVa IDs: 110701/10110, Popularity: A, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-06-10
// UVa Run Time: 0.304s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 对于大于 1 的非平方数来说，它的因子总是成对出现的，这个是解题关键。对于 n >= 1，如果 n 为平
// 方数，它的因子总数是奇数，否则是偶数，对应题目则是奇数次开关灯后灯是亮的，偶数次是灭的，判断数
// n 是否是平方数即可。

#include <bits/stdc++.h>

using namespace std;

int main(int ac, char *av[])
{
	unsigned int n;
	
	while (cin >> n, n)
	{
		int t = sqrt(n);
		cout << ((t * t == n) ? "yes" : "no") << endl;
	}
	
	return 0;
}
