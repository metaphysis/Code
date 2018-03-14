// Bee Maja （蜜蜂 Maja）
// PC/UVa IDs: 111204/10182, Popularity: B, Success rate: high Level: 2
// Verdict: Accepted
// Submission Date: 2011-11-01
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 模拟蜜蜂 Willi 的移动，根据两个坐标系的规律来生成坐标。规律是：数字组成的六边形，每一边的数字
// 递变规律是一样的。如 9，10，11，12，13，14，15，16，17，18，19，9 这 12 个数字组成的六边
// 形，左下边由 9，10，11 组成，横坐标是依次减一，纵坐标不变，对于其他边也有类似的规律，例外的是
// 右下边，由于只有 8，9 两个数，需要特殊处理组成该条边的数字。处理时的起始蜂房编号选择 1，2，9，
// 22，... ，其相邻编号之差形成一个初始项为 1，差为 6 的等差数列。由于起始处理蜂房编号的关系，需
// 要适当放宽需要计算的蜂房坐标数量，否则会有一部分蜂房编号因为循环的关系而得不到计算。

#include <bits/stdc++.h>

using namespace std;

#define MAXN 100200

int offset[5][2] = { { -1, 0 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 0, 1 } };
pair<int, int> maja[MAXN + 2000];

int main(int ac, char *av[])
{
	for (int i = 1, j = 1, k = 0; i < MAXN ; i += j, j += 6, k++)
	{
		maja[i] = make_pair(0, k);
		for (int m = 0; m < k; m++)
			maja[i - m] = make_pair(m, k - m);

		int current = i;
		for (int m = 0; m < 5; m++)
			for (int n = 0; n < k; n++)
			{
				int x = maja[current].first + offset[m][0];
				int y = maja[current].second + offset[m][1];
				maja[current + 1] = make_pair(x, y);
				current++;
			}
	}

	int willi;
	while (cin >> willi)
		cout << maja[willi].first << " " << maja[willi].second << endl;

	return 0;
}
