// The Problem With the Problem Setter （命题者的难题）
// PC/UVa IDs: 111008/10092, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-08
// UVa Run Time: 0.060s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [Problem Description]
// So many students are interested in participating in this year’s regional
// programming contest that we have decided to arrange a screening test to
// identify the most promising candidates. This test may include as many as 100
// problems drawn from as many as 20 categories. I have been assigned the job of
// setting problems for this test.
//
// At first the job seemed to be very easy, since I was told that I would be
// given a pool of about 1,000 problems divided into appropriate categories.
// After getting the problems, however, I discovered that the original authors
// often wrote down multiple category-names in the category fields. Since no
// problem can used in more than one category and the number of problems needed
// for each category is fixed, assigning problems for the test is not so easy.
//
// [Input]
// The input file may contain multiple test cases, each of which begins with a
// line containing two integers, nk and np , where nk is the number of categories
// and np is the number of problems in the pool. There will be between 2 and 20
// categories and at most 1,000 problems in the pool.
//
// The second line contains nk positive integers, where the ith integer specifies
// the number of problems to be included in category i (1 ≤ i ≤ nk ) of the test.
// You may assume that the sum of these nk integers will never exceed 100. The
// jth (1 ≤ j ≤ np ) of the next np lines contains the category information of
// the jth problem in the pool. Each such problem category specification starts
// with a positive integer specifying the number of categories in which this
// problem can be included, followed by the actual category numbers.
//
// A test case containing two zeros for nk and np terminates the input.
//
// [Output]
// For each test case, print a line reporting whether problems can be successfully
// selected from the pool under the given restrictions, with 1 for success and
// 0 for failure.
//
// In case of successful selection, print nk additional lines where the ith line
// contains the problem numbers that can be included in category i. Problem
// numbers are positive integers not greater then np and each two problem numbers
// must be separated by a single space. Any successful selection will be accepted.
//
// [Sample Input]
// 3 15
// 3 3 4
// 2 1 2
// 1 3
// 1 3
// 1 3
// 1 3
// 3 1 2 3
// 2 2 3
// 2 1 3
// 1 2
// 1 2
// 2 1 2
// 2 1 3
// 2 1 2
// 1 1
// 3 1 2 3
// 3 15
// 7 3 4
// 2 1 2
// 1 1
// 1 2
// 1 2
// 1 3
// 3 1 2 3
// 2 2 3
// 2 2 3
// 1 2
// 1 2
// 2 2 3
// 2 2 3
// 2 1 2
// 1 1
// 3 1 2 3
// 0 0
//
// [Sample Output]
// 1
// 8 11 12
// 1 6 7
// 2 3 4 5
// 0
//
// [解题方法]
// 此题和 UVa 10249 类似，可以建模成求最大流问题。设立源点 source，从源点到每道题目
// 之间弧的容量为 1，每道题目到各个类别之间弧的容量为 1，题目类别到汇点 sink 之间弧的
// 容量为该类别所要求的题目数，然后求此图的最大流能否达到题目要求数。

#include <bits/stdc++.h>

using namespace std;

#define MAXCATEGORY 21
#define MAXPROBLEM 1001
#define MAXV 1030	    // 最大顶点数。
#define UNSOLVABLE 0	// 无安排方案。
#define SOLVABLE 1	    // 存在安排方案。
#define DUMMY (-1)	    // 表示顶点无父亲顶点。

struct edge
{
	int vertex;	        // 相连的顶点。
	int capacity;	    // 容量。
	int flow;	        // 流量。
	int residual;	    // 残余流量。
};

edge edges[MAXV][MAXV];		// 有向图的边。
int degree[MAXV];		    // 有向图中顶点的度。
int parents[MAXV];		    // 遍历标记，当前顶点的父亲顶点。
bool discovered[MAXV];		// 遍历标记，是否已发现。

// 使用宽度优先遍历找到一条从源点到汇点的剩余流量为正的通路。从源到汇的任意增广路都能
// 增加总流量，因此可以借用宽度优先遍历，需要注意的是，只能沿着“还能增广”（即残余容量
// 为正数）的边走，因此需要在遍历过程中判断残余容量是否为正，以帮助宽度优先遍历区分开
// 饱和边和非饱和边。
void breadthFirstSearch(int source, int sink)
{
	queue<int> vertices;

	vertices.push(source);
	discovered[source] = true;

	while (!vertices.empty())
	{
		int v = vertices.front();
		vertices.pop();
		for (int i = 0; i < degree[v]; i++)
			// 检查是否为饱和边。
			if (edges[v][i].residual > 0)
			{
				if (discovered[edges[v][i].vertex] == false)
				{
					vertices.push(edges[v][i].vertex);
					discovered[edges[v][i].vertex] = true;
					parents[edges[v][i].vertex] = v;
				}

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

// 根据 BFS 的结果，从汇点 sink 到源点 source 计算通路的容量。增广的过程把尽量多的
// 残余流量转化为正流量。增广路的容量等于整条路中残余容量的最小值，正如车流的速度取
// 决于最拥挤的路段。
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

// 网络流解题。每次从源到汇寻找一条可以增加总流量的路径，并且用它增广。当没有增广路
// 存在时，算法终止，此时的流就是最大流。注意需要将每条有向边 e = （i，j） 拆分成两
// 条弧 （i，j） 和 （j，i），其中 （i，j） 的初始残余容量为 e 的容量，（j，i） 的残
// 余容量为 0，所有的弧的初始流均设为 0。事实上，任意可行的流都可以作为算法的初始流，
// 快速构造接近最大流的可行流能大大提高算法效率。
bool netflow(int source, int sink, int nTotal)
{
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
	int nCategories, nProblems;
	int nTotal, nCount, nType;
	int category[MAXCATEGORY];	// 每种类别的题目数量要求。
	int problem[MAXCATEGORY];	// 每种类型的现有题目数量。
	int source, sink;
	bool solvable;

	while (cin >> nCategories >> nProblems, nCategories || nProblems)
	{
		source = nTotal = 0;
		sink = nCategories + nProblems + 1;

		memset(degree, 0, sizeof(degree));
		memset(problem, 0, sizeof(problem));

		for (int i = 1; i <= nCategories; i++)
		{
			cin >> category[i];
			nTotal += category[i];
			// 源点到类别。
			edges[source][degree[source]++] = (edge){i, category[i], 0, category[i]};
			edges[i][degree[i]++] = (edge){source, category[i], 0, 0};
		}

		for (int i = nCategories + 1; i <= (nCategories + nProblems); i++)
		{
			cin >> nCount;
			for (int j = 1; j <= nCount; j++)
			{
				cin >> nType;
				problem[nType]++;
				// 类别到题目。
				edges[nType][degree[nType]++] = (edge){i, 1, 0, 1};
				edges[i][degree[i]++] = (edge){nType, 1, 0, 0};
			}
			
			// 题目到汇点。
			edges[i][degree[i]++] = (edge){sink, 1, 0, 1};
			edges[sink][degree[sink]++] = (edge){i, 1, 0, 0};
		}

		if (nCategories == 0)
		{
			cout << SOLVABLE << "\n";
			continue;
		}

		if (nProblems == 0)
		{
			cout << UNSOLVABLE << "\n";
			continue;
		}

		// 若某类型的题目数量少于要求的总数，则肯定不可解。
		solvable = true;
		for (int i = 1; i <= nCategories; i++)
			if (problem[i] < category[i])
			{
				solvable = false;
				break;
			}
		if (solvable == false)
		{
			cout << UNSOLVABLE << "\n";
			continue;		
		}
			
		solvable = netflow(source, sink, nTotal);

		cout << (solvable ? SOLVABLE : UNSOLVABLE) << "\n";

		if (!solvable)
			continue;

		for (int i = 1; i <= nCategories; i++)
		{
			int blank = 0;
			for (int j = 0; j < degree[i]; j++)
			{
				if (edges[i][j].residual == 0)
				{
					cout << (blank++ ? " " : "");
					cout << (edges[i][j].vertex - nCategories);
				}
			}

			cout << "\n";
		}
	}

	return 0;
}
