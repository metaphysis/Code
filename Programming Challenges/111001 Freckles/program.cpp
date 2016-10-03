// Freckles （斑点）
// PC/UVa IDs: 111001/10034, Popularity: B, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-10-03
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// 在 “Dick Van Dyke“ 的某一集中，小 Richie 尝试把他爸爸背上的斑点连成独立钟的图案。
// 但是其中一个斑点是伤疤，所以 Richie 的尝试失败了。
//
// 把 Dick 的背看成一个平面，上面有不同位置的斑点 （x，y）。你的任务是要告诉 Richie 
// 应该怎样连接所有点，使得所用的墨水最少。Richie 总是用直线段连接两个点，在画不同线
// 段之间可以将笔提起。当 Richie 结束画线时，任何一个斑点必须能够经过所画的线到达任
// 何另外一个斑点。
//
// [输入]
// 输入第一行只有一个正整数，代表测试数据的数量。接下来有一个空行。
//
// 每组数据的第一行有一个整数 n（0 < n <= 100），表示 Dick 背上的斑点数。接下来的每
// 行有两个实数 （x，y），分别代表他背上每个斑点的位置。
//
// 相邻两组输入数据之间有一个空行。
//
// [输出]
// 对于每组数据，你的程序要输出一个保留两位小数的实数，表示将所有斑点连接起来所需线段
// 的最小总长度。
//
// 相邻两组数据的输出之间应该有一个空行。
//
// [样例输入]
// 1
// 
// 3
// 1.0 1.0
// 2.0 2.0
// 2.0 4.0
//
// [样例输出]
// 3.41
//
// [解题方法]
// 该题是典型的求最小生成树问题，其中的边权即为两点的距离，利用 Prim 算法解决。

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

#define MAXV 100
#define START_POINT 1
#define MAX_DOUBLE (1.7E10)

// 边权设为距离的平方以便比较，而不是实际的距离。
struct edge
{
	int vertex;
	double weight;
};

// 图。
struct graph
{
	edge edges[MAXV + 1][MAXV + 1];
	int degree[MAXV + 1];
	int nvertices;
};

// 点。
struct point
{
	double x;
	double y;
};

// 使用 Prim 算法求最小生成树。
double prim(graph *g, int start)
{
	double distance[MAXV + 1];
	bool intree[MAXV + 1];
	double shortest = 0.0;
	
	// 初始化。
	memset(intree, false, sizeof(intree));
	for (int c = 1; c <= g->nvertices; c++)
		distance[c] = MAX_DOUBLE;

	distance[start] = 0.0;
	int vertex = start;
	while (intree[vertex] == false)
	{
		// 最短距离加上从起点 start 到此点 vertex 的距离。
		shortest += sqrt(distance[vertex]);
		
		// 该点已经在最小生成树中，更新与此点连接的点距离 start 的距离。
		intree[vertex] = true;
		for (int c = 0; c < g->degree[vertex]; c++)
		{
			int neighbor = g->edges[vertex][c].vertex;
			double weight = g->edges[vertex][c].weight;
			if (distance[neighbor] > weight && intree[neighbor] == false)
				distance[neighbor] = weight;
		}

		// 寻找下一条 ”从树中指向树外“ 的边中边权值最小的一条。
		vertex = START_POINT;
		double smallest = MAX_DOUBLE;
		for (int c = 1; c <= g->nvertices; c++)
			if (intree[c] == false && smallest > distance[c])
			{
				smallest = distance[c];
				vertex = c;
			}
	}
	
	return shortest;
}

int main(int ac, char *av[])
{
	int cases, n;
	double x, y;
	vector < point > points;
	graph g;

	cin >> cases;
	while (cases--)
	{
		// 读入点坐标数据。
		cin >> n;
		points.clear();
		points.resize(n + 1);
		for (int p = 1; p <= n; p++)
		{
			cin >> x >> y;
			points[p] = (point){x, y};
		}
		
		// 建边，边权值为两点距离的平方，暂时不将其距离计算出来。
		g.nvertices = n;
		memset(g.degree, 0, sizeof(g.degree));
		for (int current = 1; current <= (n - 1); current++)
			for (int next = current + 1; next <= n; next++)
			{
				double dx = abs(points[current].x - points[next].x);
				double dy = abs(points[current].y - points[next].y);
				double distance = dx * dx + dy * dy;
				
				g.edges[current][g.degree[current]++] = (edge){next, distance};
				g.edges[next][g.degree[next]++] = (edge){current, distance};
			}
			
		// 任意从一个顶点开始求最小生成树，默认从序号为 START_POINT 的点开始，从任意
		// 点开始应该是同样的。
		cout.precision(2);
		cout.setf(ios::fixed | ios::showpoint);
		cout << prim(&g, START_POINT) << endl;
		
		// 输出空行。
		if (cases)
			cout << endl;
	}
	
	return 0;
}
