// Airlines （航线）
// PC/UVa IDs: 111208/10075, Popularity: C, Success rate: high Level: 3
// Verdict: Accepted
// Submission Date: 2011-11-01
// UVa Run Time: 0.060s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 该题把求球面上两点的曲面距离和加权图每对结点之间的最短路问题结合起来了。
// 该题的第一个关键是求球面上两点的距离，而计算球面上两点的距离是有固定的公式的，很方便求。求出了
// 曲面距离，则可以通过 Floyd-Warshall 算法计算任意点对之间的最短路径长度，从而可以顺利解决本题。
//
// 设点 p 的纬度和经度为（plat，plong），地球的半径为 R，则 p 和 q 之间的球面距离为（单位为弧度）：
//
// d(p, q) = R * arccos((sin(plat)sin(qlat) + cos(plat)cos(qlat)cos(plong − qlong))

#include <bits/stdc++.h>

using namespace std;

#define MAXN 100
#define MAXM 300
#define MAXQ 10000
#define PI 3.141592653589793
#define EARTH_RADIUS 6378
#define MAXINT (1L << 20)

int weight[MAXN + 1][MAXN + 1];
pair < double, double > locations[MAXN + 1];
map < string, int > cities;

// 将角度转换为弧度。
inline double radians(double degree)
{
	return (degree * 2.0 * PI / 360.0);
}

// 计算两个城市间航线的距离。
int calDistance(int start, int end)
{
	// 将角度转换为弧度。
	double plat = radians(locations[start].first);
	double plong = radians(locations[start].second);
	double qlat = radians(locations[end].first);
	double qlong = radians(locations[end].second);

	// 利用公式计算球面上两点的曲线距离。
	double distance = EARTH_RADIUS * acos(sin(plat) * sin(qlat) +
		cos(plat) * cos(qlat) * cos(plong - qlong));

	// 四舍五入取整并返回结果。
	return (int)(distance + 0.5);
}

int main(int ac, char *av[])
{
	int n, m, q, cases = 1;
	bool printSmartEmptyLine = false;
	string city, cityStart, cityEnd;
	double latitude, longitude;

	while (cin >> n >> m >> q, n || m || q)
	{
		// 初始化。
		cities.clear();
		for (int i = 1; i <= MAXN; i++)
			for (int j = 1; j <= MAXN; j++)
				weight[i][j] = MAXINT;

		// 读入城市和其坐标。
		for (int i = 1; i <= n; i++)
		{
			cin >> city >> latitude >> longitude;
			cities[city] = i;
			locations[i] = make_pair(latitude, longitude);
		}

		// 读入航线数据。
		for (int i = 1; i <= m; i++)
		{
			cin >> cityStart >> cityEnd;

			int idStart = cities[cityStart];
			int idEnd = cities[cityEnd];

			weight[idStart][idEnd] = calDistance(idStart, idEnd);
		}

		// 使用 Floyd-Warshall 算法计算任意两个城市间的最短航线距离。
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					weight[i][j] = min(weight[i][j],
						weight[i][k] + weight[k][j]);

		// 输出空行。
		if (printSmartEmptyLine)
			cout << endl;
		else
			printSmartEmptyLine = true;

		// 输出测试例数。
		cout << "Case #" << cases++ << endl;
		
		// 输出指定城市间的航线距离。
		for (int i = 1; i <= q; i++)
		{
			cin >> cityStart >> cityEnd;

			int idStart = cities[cityStart];
			int idEnd = cities[cityEnd];

			if (weight[idStart][idEnd] < MAXINT)
				cout << weight[idStart][idEnd] << " km" << endl;
			else
				cout << "no route exists" << endl;
		}
	}

	return 0;
}
