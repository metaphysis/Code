// The Grand Dinner （丰盛的晚餐）
// PC/UVa IDs: 111007/10249, Popularity: C, Success rate: high Level: 4
// Verdict: Accepted
// Submission Date: 2011-10-09
// UVa Run Time: 3.324s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 网络流解法：源点 source 和每支参赛队伍之间弧的容量为参赛队伍人数，每支队伍到桌子之间弧的容量为
// 1，每张桌子到汇点 sink 弧的容量为桌子的座位数，然后使用网络流算法求最大流，如果最大流等于参赛队
// 伍总人数，则满足条件，输出方案，否则不满足条件，输出 0。此处使用宽度优先遍历的 Ford-Fullerson
// 增广路方法，又名 Edmonds-Karp 算法，算法效率为 O（V*E*E），对于顶点数和边数增加的题目，可以
// 使用最短扩增路 （Shortest Augment Path，SAP） 算法。

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define MAXTEAMS 71
#define MAXTABLES 51
#define MAXV 130	// 最大顶点数。
#define UNSOLVABLE 0	// 无安排方案。
#define SOLVABLE 1	// 存在安排方案。
#define DUMMY (-1)	// 表示顶点无父亲顶点。

struct edge
{
	int vertex;	// 相连的顶点。
	int capacity;	// 容量。
	int flow;	// 流量。
	int residual;	// 残余流量。
};

edge edges[MAXV][MAXV];		// 有向图的边。
int degree[MAXV];		// 有向图中顶点的度。
int parents[MAXV];		// 遍历标记，当前顶点的父亲顶点。
bool discovered[MAXV];		// 遍历标记，是否已发现。

// 使用宽度优先遍历找到一条从源点到汇点的剩余流量为正的通路。从源到汇的任意增广路都能增加总流量，因
// 此可以借用宽度优先遍历，需要注意的是，只能沿着“还能增广”（即残余容量为正数）的边走，因此需要在
// 遍历过程中判断残余容量是否为正，以帮助宽度优先遍历区分开饱和边和非饱和边。
void breadthFirstSearch(int source, int sink)
{
	queue < int > vertices;

	vertices.push(source);
	discovered[source] = true;

	while (!vertices.empty())
	{
		int v = vertices.front();
		vertices.pop();
		for (int i = 0; i < degree[v]; i++)
			// 检查是否为饱和边。
			if (edges[v][i].residual > 0)
				if (discovered[edges[v][i].vertex] == false)
				{
					vertices.push(edges[v][i].vertex);
					discovered[edges[v][i].vertex] = true;
					parents[edges[v][i].vertex] = v;

					// 遍历到汇点后说明已经找到一条增广路，可以退出。
					if (edges[v][i].vertex == sink)
						return;
				}
	}
}

// 找到顶点 x 与顶点 y 之间的有向边。
edge *findEdge(int x, int y)
{
	for (int i = 0; i < degree[x]; i++)
		if (edges[x][i].vertex == y)
			return &edges[x][i];
}

// 增广，注意对前向弧和反向弧的处理。
void augmentPath(int source, int sink, int volume)
{
	if (source == sink)
		return;

	edge *e = findEdge(parents[sink], sink);
	e->flow += volume;
	e->residual -= volume;

	e = findEdge(sink, parents[sink]);
	e->residual += volume;

	augmentPath(source, parents[sink], volume);
}

// 根据 BFS 的结果，从汇点 sink 到源点 source 计算通路的容量。增广的过程把尽量多的残余流量转
// 化为正流量。增广路的容量等于整条路中残余容量的最小值，正如车流的速度取决于最拥挤的路段。
int pathVolume(int source, int sink)
{
	if (parents[sink] == DUMMY)
		return 0;

	edge *e = findEdge(parents[sink], sink);
	if (source == parents[sink])
		return (e->residual);
	else
		return (min(pathVolume(source, parents[sink]), e->residual));
}

// 初始化搜索变量。
void initializeSearch()
{
	memset(discovered, false, sizeof(discovered));
	memset(parents, DUMMY, sizeof(parents));
}

// 网络流解题。每次从源到汇寻找一条可以增加总流量的路径，并且用它增广。当没有增广路存在时，算法终
// 止，此时的流就是最大流。注意需要将每条有向边 e = （i，j） 拆分成两条弧 （i，j） 和 （j，i），
// 其中 （i，j） 的初始残余容量为 e 的容量，（j，i） 的残余容量为 0，所有的弧的初始流均设为 0。
// 事实上，任意可行的流都可以作为算法的初始流，快速构造接近最大流的可行流能大大提高算法效率。
bool netflow(int source, int sink, int nTotal)
{
	// Edmonds-Karp 算法。
	int maxFlow = 0, volume;

	initializeSearch();
	breadthFirstSearch(source, sink);
	volume = pathVolume(source, sink);
	while (volume)
	{
		maxFlow += volume;
		augmentPath(source, sink, volume);
		initializeSearch();
		breadthFirstSearch(source, sink);
		volume = pathVolume(source, sink);
	}

	return maxFlow == nTotal;
}

int main(int ac, char *av[])
{
	int nTeams, nTables, nTotal;	// 队伍数，桌子数，总人数。
	int nCount, maxMembers;
	int source, sink;

	while (cin >> nTeams >> nTables, nTeams || nTables)
	{
		source = nTotal = maxMembers = 0;
		sink = nTeams + nTables + 1;

		memset(degree, 0, sizeof(degree));

		// 读入参赛队人数并找参赛队的最大人数。
		for (int i = 1; i <= nTeams; i++)
		{
			cin >> nCount;
			if (maxMembers < nCount)
				maxMembers = nCount;
			nTotal += nCount;

			// 源点 source 到参赛队伍的弧。
			edges[source][degree[source]++] = (edge){i, nCount, 0, nCount};
			edges[i][degree[i]++] = (edge){source, nCount, 0, 0};
		}

		// 读入桌子座位数量。
		for (int i = nTeams + 1; i <= (nTeams + nTables); i++)
		{
			cin >> nCount;

			// 参赛队伍到桌子的弧。
			for (int j = 1; j <= nTeams; j++)
			{
				edges[j][degree[j]++] = (edge){i, 1, 0, 1};
				edges[i][degree[i]++] = (edge){j, 1, 0, 0};
			}
			
			// 桌子到汇点 sink 的弧。
			edges[i][degree[i]++] = (edge){sink, nCount, 0, nCount};
			edges[sink][degree[sink]++] = (edge){i, nCount, 0, 0};
		}

		// 若参赛队伍数为 0，则直接输出存在，但是不用输出具体方案，因为所有桌子无人坐。
		if (nTeams == 0)
		{
			cout << SOLVABLE << "\n";
			continue;
		}

		// 若桌子数为 0 或者参赛队伍中某队人数超过桌子数，则无法安排。
		if (nTables == 0 || maxMembers > nTables)
		{
			cout << UNSOLVABLE << "\n";
			continue;
		}

		bool solvable = netflow(source, sink, nTotal);

		cout << (solvable ? SOLVABLE : UNSOLVABLE) << "\n";

		if (!solvable)
			continue;

		for (int i = 1; i <= nTeams; i++)
		{
			int blank = 0;
			for (int j = 0; j < degree[i]; j++)
			{
				if (edges[i][j].residual == 0)
				{
					cout << (blank++ ? " " : "");
					cout << (edges[i][j].vertex - nTeams);
				}
			}

			cout << "\n";
		}
	}

	return 0;
}
