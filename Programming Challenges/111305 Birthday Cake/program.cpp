// Birthday Cake （生日蛋糕）
// PC/UVa IDs: 111305/10167, Popularity: C, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-11-01
// UVa Run Time: 0.192s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 枚举所有可能的 A 和 B，判断是否符合条件。

#include <iostream>
#include <cmath>

using namespace std;

#define MAXN 100

struct point
{
	int x;
	int y;
};

int main(int ac, char *av[])
{
	int N;
	point cherries[MAXN + 1];

	while (cin >> N, N)
	{
		for (int i = 1; i <= 2 * N; i++)
			cin >> cherries[i].x >> cherries[i].y;

		// 枚举所有可能的 A 和 B，统计在直线上下的樱桃数是否相等，若樱桃在直线上不满
		// 足条件。
		for (int i = -500; i <= 500; i++)
		{
			bool found = false;
			for (int j = -500; j <= 500; j++)
			{
				int up = 0, down = 0;
				bool online = false;
				for (int k = 1; k <= 2 * N; k++)
				{
					if (i * cherries[k].x + j * cherries[k].y == 0)
					{
						online = true;
						break;
					}
					else if (i * cherries[k].x + j * cherries[k].y > 0)
						up++;
					else
						down++;
				}

				if (online == false && up == down)
				{
					cout << i << " " << j << endl;
					found = true;
					break;
				}
			}

			if (found)
				break;
		}
	}

	return 0;
}
