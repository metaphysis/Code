// Steps （数轴行走）
// PC/UVa IDs: 110608/846, Popularity: A, Success rate: high Level: 2
// Verdict: Accepted
// Submission Date: 2011-09-25
// UVa Run Time: 0.016s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 所走步数对应的序列如果左右对称，那么所走的步数应该是最少的。因为最先一步和最后一步长度均必须是
// 1，又由于每一步的长度必须是非负整数，且要么比上一步步长恰好大 1，要么相等，要么小 1，则左右对
// 称的序列能在最少步数得到最大距离。如果采取左右对称的走法，设两点距离为 distance，n = sqrt
// （distance），则由于最大步数为 n 步时能达到的距离是 1 + 2 + 3 + ... + （n - 1） + n +
// （n - 1） + ... + 3 + 2 + 1 = n^2。比较两点距离 distance 与 n^2，若相等，表明只需走
// 2 * （n - 1） + 1 = 2 * n - 1 步，否则若剩余距离 distance - n^2 在 1 - （n + 1），
// 只需插入一步即可，若 distance - n^2 大于 （n + 1），则需多插入两步即可。
	
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
	
using namespace std;
	
int main(int ac, char *av[])
{
	int cases, x, y;
	
	cin >> cases;
	while (cases--)
	{
		cin >> x >> y;
		int distance = y - x;
		
		if (distance <= 3)
			cout << distance << endl;
		else
		{
			int n = sqrt(distance);
		
			if (n * n == distance)
				cout << (2 * n - 1) << endl;
			else if ((distance - n * n) <= (n + 1))
				cout << (2 * n) << endl;
			else
				cout << (2 * n + 1) << endl;
		}
	}
	
	return 0;
}
