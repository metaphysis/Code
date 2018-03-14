// Adventures in Moving: Part IV （搬家大冒险：第四部）
// PC/UVa IDs: 111108/10201, Popularity: A, Success rate: low Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-19
// UVa Run Time: 0.024s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 设到达第 i 个加油站时，剩余油量为 j 升时的最小花费为 cost[i][j]，d[m][i] 为第 m 个加油站
// 和第 i 个加油站之间的距离，p[i] 为第 i 个加油站加 1 升油的费用，则有以下状态转移方程：
//
// cost[i][j] = min{cost[m][n] + ((n - d[m][i] >= j) ? 0 : (d[m][i] + j - n) * 
// p[i] | d[m][i] <= n, 1<= m < i}
//
// 顺便给出一组测试数据和 AC 程序得到的结果：
// 10
//
// 500
// 100 1
// 300 1
// 350 1
// 501 10
//
// 101
// 100 100
// 102 1
//
// 100
//
// 101
//
// 200
// 100 10
//
// 201
// 100 10
//
// 201
// 101 10
//
// 50
// 25 10
//
// 150
// 100 10
// 151 20
//
// 150
// 100 10
// 151 20
// 152 1
//
// AC 程序给出的结果：
// 950
//
// 299
//
// Impossible
//
// Impossible
//
// 2000
//
// Impossible
//
// Impossible
//
// 500
//
// 1500
//
// 618
//
// 注意第一组数据，UVa 中的测试数据应该没有包含这样的数据，在到达 501 公里时，没有再退回到 500
// 公里处。

#include <bits/stdc++.h>

using namespace std;

#define MAXN 102	// 最大加油站数量。
#define MAXL 201	// 最大剩余油量的升数。
#define MAXINT (1 << 28)

int kilometers[MAXN];	// 加油站距离起点的距离（单位：公里）。
int price[MAXN];	// 加油站每加 1 升油的费用（单位：10美分）。
long long cost[MAXN][MAXL];	// 在加油站 i 拥有剩余油量 j 时的最小花费。
int nstations;		// 加油站总个数。

// 动态规划求花费的最小费用。
int dynamic_programming()
{
	// 初始时，置全部费用为最大值。
	for (int i = 0; i <= nstations; i++)
		for (int j = 0; j < MAXL; j++)
			cost[i][j] = MAXINT;

	// 第 0 个加油站剩余油量为 100 升时，总费用为 0。
	cost[0][100] = 0;
	for (int i = 0; i < nstations - 1; i++)
		for (int j = 0; j < MAXL; j++)
			if (cost[i][j] < MAXINT)
			{
				// 计算从加油站 i，剩余油量为 j 升时到达下一个加油站 next，
				// 剩余油量为 k 升时的最小费用。
				int next = i + 1;
				while ((kilometers[next] - kilometers[i]) <= j && next < nstations)
				{
					// 计算剩余油量。若剩余油量大于等于 k 升，则不需加油，否则需要加油。
					int remain = j - (kilometers[next] - kilometers[i]);
					for (int k = 0; k <= remain; k++)
						cost[next][k] =
						min(cost[i][j], cost[next][k]);

					for (int k = remain + 1; k < MAXL; k++)
						cost[next][k] = min(cost[i][j] +
							(k - remain) * price[next], cost[next][k]);

					next++;
				}
			}

	// 取到达最后一个加油站时，剩余油量为 100 升时的费用。
	return cost[nstations - 1][100];
}

// 判断大城市在给定限制下是否可达。
bool reachable(int end)
{
	// 和大城市距离为 0。
	if (end == 0)
		return true;

	// 和大城市的距离不为 0，但是无加油站。
	if (nstations == 2)
		return false;

	// 第一个加油站离起点距离大于 100 公里。
	if (kilometers[1] > 100)
		return false;

	// 最后一个加油站离终点距离大于 100 公里。
	if (end - kilometers[nstations - 2] > 100)
		return false;
	
	// 任意两个加油站之间距离大于 200 公里。
	for (int i = 2; i < nstations; i++)
		if (kilometers[i] - kilometers[i - 1] > 200)
			return false;

	return true;
}

int main(int ac, char *av[])
{
	int cases, end;
	bool printStupidEmptyLine = false;
	string line;

	// 读入测例数。
	cin >> cases;
	cin.ignore();
	getline(cin, line);

	while (cases--)
	{
		// 读入终点和起点间的距离。
		cin >> end;
		cin.ignore();

		// 设置起点为一个虚拟加油站，加油价格为 0，因为不会在此虚拟加油站加油。
		nstations = 0;
		kilometers[nstations] = 0;
		price[nstations] = 0;
		nstations++;

		// 读取实际的加油站距离和价格。
		while (getline(cin, line), line.length())
		{
			istringstream iss(line);
			iss >> kilometers[nstations] >> price[nstations];
			nstations++;
		}

		// 设置终点为一个虚拟加油站，加油价格为最大值，以免在最后一个虚拟加油站加油。
		kilometers[nstations] = end;
		price[nstations] = 2000;
		nstations++;

		// 输出空行。
		if (printStupidEmptyLine)
			cout << endl;
		else
			printStupidEmptyLine = true;

		// 判断是否可达，若可达则计算最小花费。
		if (reachable(end) == false)
			cout << "Impossible" << endl;
		else
			cout << dynamic_programming() << endl;
	}

	return 0;
}
