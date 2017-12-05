// Bicoloring （双着色）
// PC/UVa IDs: 110901/10004, Popularity: A, Success rate: high Level: 1
// Verdict: Accepted
// Submission Date: 2011-09-25
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

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
