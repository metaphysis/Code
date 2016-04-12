// UVa Problem 117 - The Postal Worker Rings Once
// Verdict: Accepted
// Submission Date: 2016-04-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 图论，欧拉路径。根据题意，度为奇数的节点数为 1 的情况不可能出现，度为奇数的节点数
// 目只可能为 0 或者 2。当度为奇数的节点数为 0 时，很好办，走遍所有边仅一次的最小花
// 费是所有边权的和，而当度为奇数的数目为 2 时，最小花费是所有边权的和加上这两个度数
// 为奇数的节点之间的最短路径长度。为了简便，可以采用 Floyd-Warshall 算法来得到两点
// 间的最短路径长度。

#include <iostream>

using namespace std;

const int MAXV = 27, INT_MAX = 10240;

// 邻接矩阵表示图。
struct graph
{
	int weight[MAXV][MAXV], nvertices;
};

graph g;
int lengthOfStreet, crossroad[MAXV];
	
// 利用 Floyd-Warshall 算法计算所有点对之间的最短距离。
void floydWarshall()
{
	int vertices = g.nvertices;

	for (int i = 1; i <= vertices; i++)
		g.weight[i][i] = 0;
    
	for (int k = 1; k <= vertices; k++)
		for (int i = 1; i <= vertices; i++)
			for (int j = 1; j <= vertices; j++)
				g.weight[i][j] = min(g.weight[i][j], g.weight[i][k] + g.weight[k][j]);
}

void initialize()
{
	lengthOfStreet = 0;
	g.nvertices = MAXV - 1;
	for (int i = 1; i < MAXV; i++)
	{
		crossroad[i] = 0;
		for (int j = 1; j < MAXV; j++)
			g.weight[i][j] = INT_MAX;
	}
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    initialize();

    string street;
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
				floydWarshall();
				cout << (lengthOfStreet + g.weight[start][end]) << "\n";
			}
			else
				cout << lengthOfStreet << "\n";

            initialize();
		}
		else
		{
			lengthOfStreet += street.length();
			char front = street.front(), back = street.back();
			g.weight[front - 'a' + 1][back - 'a' + 1] = street.length();
			g.weight[back - 'a' + 1][front - 'a' + 1] = street.length();
			crossroad[front - 'a' + 1]++;
			crossroad[back - 'a' + 1]++;
		}
	}

	return 0;
}
