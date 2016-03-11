// The Tourist Guide （导游）
// PC/UVa IDs: 110903/10099, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-09-27
// UVa Run Time: 0.020s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// Mr. G. 在孟加拉国的一家旅游公司工作。他当前的任务是带一些游客去一个遥远的城市。和所有国家一样，
// 一些城市之间有双向道路。每对相邻城市之间都有一条公交线路，每条线路都规定了自己最大乘客数目。Mr.
// G. 有一份包含城市间道路状况和公交车最大载客容量的地图。
//
// 往往无法一次性地将所有乘客带往目的地。例如，在下面 7 个城市的地图中，边代表道路，每条边上的数字
// 代表这条道路上公交车的最大载客量。
//
//                   60
//            [2]--------[5]
//           /   \          \
//       30/      \25        \20
//       /    10   \    35    \
//     [1]--------[4]--------[7]
//      \         /          /
//     15\      / 40       /30
//        \   /          /
//         [3]--------[6]
//               20
//
// 如果 Mr. G. 要将 99 位乘客从城市 1 带到城市 7，则至少需要往返 5 次（他必须陪同每一群游客）。
// 最佳路线是 1 - 2 - 4 - 7。
//
// 帮助 Mr. G. 找出将所有游客带到目的地，且往返次数最少的线路。
//
// [输入]
// 输入包含若干组数据。每组数据的第一行有两个整数 N （N <= 100） 和 R，分别表示城市的数量和道路
// 的数量。接下来的 R 行有 3 个整数 （C1，C2，P），其中 C1 和 C2 为城市编号，P（P > 1） 是该
// 道路上公交车的最大载客量。各城市编号为 1 ～ N 的连续整数。第 R + 1 行包含 3 个整数 （S，D，
// T），分别表示出发城市，目的城市的编号和游客的数量。N = R = 0 时输入结束。
//
// [输出]
// 对于每组输入数据，按照样例格式先输出一行数据编号，接下来在单独的一行中输出最少的往返次数。在每组
// 数据的输出后打印一个空行。
//
// [样例输入]
// 7 10
// 1 2 30
// 1 3 15
// 1 4 10
// 2 4 25
// 2 5 60
// 3 4 40
// 3 6 20
// 4 7 35
// 5 7 20
// 6 7 30
// 1 7 99
// 0 0
//
// [样例输出]
// Scenario #1
// Minimum Number of Trips = 5
//
// [解题方法]
// 应用 Floyd-Warshall 算法可以方便的计算 Maxmin 距离从而可以容易的解决本题。注意导游必须陪同
// 每一群游客的意思是假设公交线路载客量为 C，则一次能载游客为 C - 1，因为包括了导游，则往返的次数
// 应该是 P / （C - 1） + （P % （C - 1） ？ 1 ： 0），同时不要忘了在每次输出后加空行。
//
// 有关 Floyd-Warshall 算法的更多应用，可参考网页：
// http://aduni.org/courses/algorithms/courseware/handouts/Reciation_07.html#25504。

#include <iostream>

using namespace std;

#define MAXV 101
#define INT_MAX (-1)

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// 邻接矩阵。
struct graph
{
	int weight[MAXV][MAXV];
	int nvertices;
};

// 利用 Floyd-Warshall 算法计算 Maxmin 距离。
int floyd_warshall(graph * g, int cstart, int cend)
{
	int vertices = g->nvertices;

	for (int i = 1; i <= vertices; i++)
		g->weight[i][i] = 0;

	for (int k = 1; k <= vertices; k++)
		for (int i = 1; i <= vertices; i++)
			for (int j = 1; j <= vertices; j++)
				g->weight[i][j] =
					max(g->weight[i][j],
					min(g->weight[i][k], g->weight[k][j]));

	return g->weight[cstart][cend];
}

// 读入图的数据，cities 为城市数，roads 为公交路线数。
void read_graph(graph * g, int cities, int roads)
{
	int cfirst, csecond, passengers;

	for (int i = 1; i < MAXV; i++)
		for (int j = 1; j < MAXV; j++)
			g->weight[i][j] = INT_MAX;

	g->nvertices = cities;

	for (int r = 0; r < roads; r++)
	{
		cin >> cfirst >> csecond >> passengers;

		g->weight[cfirst][csecond] = passengers;
		g->weight[csecond][cfirst] = passengers;
	}
}

int main(int ac, char *av[])
{
	int cities, roads;
	int cstart, cend, tourists;
	int trips, cases = 1;
	graph g;

	while (cin >> cities >> roads, cities || roads)
	{
		// 读入图的数据。
		read_graph(&g, cities, roads);

		// 读入起始城市和终点城市及游客数量。
		cin >> cstart >> cend >> tourists;

		// 利用 Floyd-Warshall 算法计算 Maxmin 距离。
		int maxmin = floyd_warshall(&g, cstart, cend);

		maxmin = maxmin - 1;

		// 若不能整除，则需要多一次往返。
		trips = tourists / maxmin + (tourists % maxmin ? 1 : 0);

		// 注意输出空行。
		cout << "Scenario #" << cases++ << endl;
		cout << "Minimum Number of Trips = " << trips << endl << endl;
	}

	return 0;
}
