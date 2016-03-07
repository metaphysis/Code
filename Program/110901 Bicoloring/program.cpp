// Bicoloring （双着色）
// PC/UVa IDs: 110901/10004, Popularity: A, Success rate: high Level: 1
// Verdict: Accepted
// Submission Date: 2011-09-25
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// 四色定理 （four-color theorem） 说的是：对于任意一个平面地图，可以只用四种颜色为它着
// 色，使得每个区域均被着色，且每两个相邻区域的颜色都不相同。定理在提出 100 多年后的 1976 年，人
// 们才成功的借助计算机证明了它。现在请求你来解决这个问题的一个简化版本：判断一个给定的平面地图是否
// 可以只用红色和黑色着色，使得每两个相邻区域的颜色不同。假设地图总是连通的，无向的，且不包含自环 （
// 即从某个顶点到它自己的边）。
//
// [输入]
// 输入包含若干组数据。每组数据的第一行有一个整数 n （1 < n < 200），表示顶点的数量。每个顶点用
// 0 ～ （n - 1） 之间的数表示。第二行为一个整数 l，表示边的数量。接下来的 l 行每行用两个顶点的
// 序号来描述一条边。当 n = 0 时，输入结束，你的程序不应处理这一行。
//
// [输出]
// 判断输入的图是否可以双着色，并按照样例的格式输出结果。
//
// [样例输入]
// 3
// 3
// 0 1
// 1 2
// 2 0
// 9
// 8
// 0 1
// 0 2
// 0 3
// 0 4
// 0 5
// 0 6
// 0 7
// 0 8
// 0
//
// [样例输出]
// NOT BICOLORABLE.
// BICOLORABLE.
//
// [解题方法]
// 解题思路比较简单，使用宽度优先遍历 （BFS） 模拟着色过程并检测即可，若在遍历过程中发现已处理点
// 的颜色与当前顶点的颜色相同，则表明存在冲突而不能着色。

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define MAXV 200
#define MAXDEGREE 200

#define RED 0
#define BLACK 1

// 图结构。
struct graph
{
	int edges[MAXV][MAXDEGREE];	// 使用邻接表来表示边。
	int degree[MAXV];		// 顶点的边数。
};

bool processed[MAXV];
bool discovered[MAXV];
int color[MAXV];	// 顶点的颜色

// 使用宽度优先搜索模拟着色过程。
bool bicoloring_breadth_first_search(graph * g, int start)
{
	queue <int> q;

	q.push(start);
	discovered[start] = true;

	while (!q.empty())
	{
		// 弹出队列首元素进行处理。
		int v = q.front();
		q.pop();

		// 标记顶点 v 为已处理。
		processed[v] = true;
		
		// 遍历与顶点 v 相连的顶点。
		for (int i = 0; i < g->degree[v]; i++)
		{
			if (discovered[g->edges[v][i]] == false)
			{
				q.push(g->edges[v][i]);
				discovered[g->edges[v][i]] = true;
			}

			// 若未处理则染色，若已处理则检查颜色是否相同。
			if (processed[g->edges[v][i]] == false)
				color[g->edges[v][i]] = (color[v] == RED ? BLACK : RED);
			else if (color[g->edges[v][i]] == color[v])
				return false;
		}
	}

	return true;
}

int main(int ac, char *av[])
{
	int nvertices, nedges, x, y;
	graph g;

	while (cin >> nvertices, nvertices)
	{
		// 初始化图。
		memset(g.degree, 0, sizeof(g.degree));

		// 读入图。
		cin >> nedges;
		for (int c = 1; c <= nedges; c++)
		{
			cin >> x >> y;
			
			g.edges[x][g.degree[x]] = y;
			g.degree[x]++;
			
			g.edges[y][g.degree[y]] = x;
			g.degree[y]++;			
		}

		// 初始化宽度优先搜索所使用的标记。默认起点染成红色。
		memset(processed, false, sizeof(processed));
		memset(discovered, false, sizeof(discovered));
		memset(color, 0, sizeof(color));

		// 使用宽度优先搜索着色。
		bool bicolorable = bicoloring_breadth_first_search(&g, 0);
		
		// 输出结果。
		cout << (bicolorable ? ("BICOLORABLE.") : ("NOT BICOLORABLE.")) << endl;
	}

	return 0;
}
