// Dermuba Triangle （Dermuba 三角）
// PC/UVa IDs: 111207/10233, Popularity: C, Success rate: high Level: 2
// Verdict: Accepted
// Submission Date: 2011-11-01
// UVa Run Time: 0.016s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
	double x;
	double y;
};

double calDistance(unsigned n, unsigned m)
{
	point nn, mm;

	// 计算编号为 n 的房子的横坐标和纵坐标，start 为 n 所在行的起始房子编号。
	long long start = (long long)sqrt(n);
	nn.x = (n - start * start - start) / 2.0;
	nn.y = 0.0;
	if (start)
	{
		nn.y = (start - 1) * (sqrt(3) / 2.0);
		nn.y += ((start + n) & 1 ? (sqrt(3) / 3.0) : (sqrt(3) / 2.0));
	}
	
	// 计算编号为 m 的房子的横坐标和纵坐标。
	start = (long long)sqrt(m);
	mm.x = (m - start * start - start) / 2.0;
	mm.y = 0.0;
	if (start)
	{
		mm.y = (start - 1) * (sqrt(3) / 2.0);
		mm.y += ((start + m) & 1 ? (sqrt(3) / 3.0) : (sqrt(3) / 2.0));
	}

	// 计算距离。
	return sqrt(pow(nn.x - mm.x, 2) + pow(nn.y - mm.y, 2));
}

int main(int ac, char *av[])
{
	unsigned n, m;

	cout.precision(3);
	cout.setf(ios::fixed | ios::showpoint);

	while (cin >> n >> m)
		cout << calDistance(n, m) << endl;

	return 0;
}
