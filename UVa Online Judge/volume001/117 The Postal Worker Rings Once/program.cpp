// UVa Problem 117 - The Postal Worker Rings Once
// Verdict: Accepted
// Submission Date: 2011-12-21
// UVa Run Time: 0.040s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 图论，欧拉路径。
// 根据题意，度为奇数的节点数为 1 的情况不可能出现，度为奇数的节点数目只可能为 0 或者 2。当度为
// 奇数的节点数为 0 时，很好办，走遍所有边仅一次的最小花费是所有边权的和，而当度为奇数的数目为 2
// 时，最小花费是所有边权的和加上这两个度数为奇数的节点之间的最短路径长度。
// 为了简便，可以采用 floyd_warshall 算法来得到两点间的最短路径长度。

#include <iostream>

using namespace std;

#define MAXV 27
#define INT_MAX (1 << 10)

// 邻接矩阵。
struct graph
{
	int weight[MAXV][MAXV];
	int nvertices;
};

// 利用 Floyd-Warshall 算法计算所有点对之间的最短距离。
void floyd_warshall(graph * g)
{
	int vertices = g->nvertices;

	for (int i = 1; i <= vertices; i++)
		g->weight[i][i] = 0;

	for (int k = 1; k <= vertices; k++)
		for (int i = 1; i <= vertices; i++)
			for (int j = 1; j <= vertices; j++)
				g->weight[i][j] =
					min(g->weight[i][j],
					g->weight[i][k] + g->weight[k][j]);
}

int main(int argc, char const *argv[])
{
	graph g;
	int length;
	string street;
	int crossroad[MAXV];

	length = 0;
	g.nvertices = MAXV;
	for (int i = 1; i < MAXV; i++)
	{
		crossroad[i] = 0;
		for (int j = 1; j < MAXV; j++)
			g.weight[i][j] = INT_MAX;
	}

	while (cin >> street)
	{
		if (street == "deadend")
		{
			int start, end;
			bool found = false;
			for (int i = 1; i < MAXV; i++)
				if (crossroad[i] & 1)
				{
					if (found == false)
						start = i;
					else
						end = i;
					found = true;
				}

			if (found)
			{
				floyd_warshall(&g);
				cout << (length + g.weight[start][end]) << endl;
			}
			else
				cout << length << endl;

			length = 0;
			g.nvertices = MAXV;
			for (int i = 1; i < MAXV; i++)
			{
				crossroad[i] = 0;
				for (int j = 1; j < MAXV; j++)
					g.weight[i][j] = INT_MAX;
			}
		}
		else
		{
			length += street.length();
			g.weight[street[0] - 'a' + 1][street[street.length() -
					1] - 'a' + 1] = street.length();
			g.weight[street[street.length() - 1] - 'a' +
				1][street[0] - 'a' + 1] = street.length();
			crossroad[street[0] - 'a' + 1]++;
			crossroad[street[street.length() - 1] - 'a' + 1]++;
		}
	}

	return 0;
}
