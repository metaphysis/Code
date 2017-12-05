// Playing With Wheels （摆弄轮子）
// PC/UVa IDs: 110902/10067, Popularity: C, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-09-26
// UVa Run Time: 0.380s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// 下图是一个数学仪器，连续的数字 0 ～ 9 按顺时针顺序被印在每个齿轮的外围。每个齿轮的最高的数字一
// 起构成一个四位数。例如，下面的这些齿轮构成的整数为 8056。每个齿轮有两个按钮，按左箭头时齿轮将
// 按顺时针方向移动一个字母，按右箭头时则是沿相向相反的方向运动。
//
//        8             0             5             6     
//     7     9       9     1       4     6       5     7  
//   6         0   8         2   3         7   4         8
//   5         1   7         3   2         8   3         9
//     4     2       6     4       1     9       2     0  
//        3             5             0             1     
// 
//     <<=  =>>      <<=  =>>      <<=  =>>      <<=  =>> 
//
// 开始时，齿轮的顶端数字构成 S1S2S3S4，给你 n 个禁止的数 Fi1Fi2Fi3Fi4 （1 <= i <= n） 和
// 一个目标数T1T2T3T4，你的任务是在中途不能得到禁止数的情况下，尽量少地按下按钮来得到目标数。
//
// [输入]
// 输入第一行有一个整数 N，代表测试数据的数量。接下来有一个空行。
// 每组数据的第一行描述了这些齿轮的初始状态，用四个数表示，其中每两个相邻数字用一个空格隔开。下面
// 一行为目标数。第三行有一个整数 n，表示禁止数的个数。接下来的 n 行每行有一个禁止数。相邻两组输
// 入数据之间有一个空行。
//
// [输出]
// 对于每一组输入数据，输出第一行，表示需要按下按钮的最少次数。如果无法完成任务，输出“-1”。
//
// [样例输入]
// 2
// 
// 8 0 5 6
// 6 5 0 8
// 5
// 8 0 5 7
// 8 0 4 7
// 5 5 0 8
// 7 5 0 8
// 6 4 0 8
// 0 0 0 0
// 5 3 1 7
// 8
// 0 0 0 1
// 0 0 0 9
// 0 0 1 0
// 0 0 9 0
// 0 1 0 0
// 0 9 0 0
// 1 0 0 0
// 9 0 0 0
//
// [样例输出]
// 14
// -1
//
// [解题方法]
// 由题意可知，每个四位数通过按动左右箭头可以变成其他八个数，实际上这些数之间构成了一个无自环的无向
// 连通图，从给定数出发找目标数相当于寻找给定顶点之间的最短路径。由于在中途中能得到禁止数，则可以将
// 这些禁止数所代表的顶点从图中去掉后再寻找最短路径。
//
// 提示：UVa 上的数据格式并不像题目描述的那样严格，所以在读入数据时需要注意，对于算法正确，提交却
// 总是 WA 的程序，可以尝试以下测试数据 （注意该测试数据第一行后并没有空行，而中间有空行，UVa 上
// 的数据经常出现此种情况）：
// 2
// 1 7 4 0
// 9 4 8 8
// 2
// 4 5 5 1
// 7 1 1 5
// 
// 3 4 8 4
// 9 9 2 5
// 5
// 3 3 3 7
// 4 3 8 0
// 8 8 0 6
// 8 1 9 8
// 9 7 2 2

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define MAXV 10000
#define MAXDEGREE 8

#define NBASE 10
#define NDIGITS 4

// 图结构。
struct graph
{
	int edges[MAXV][MAXDEGREE];	// 使用邻接表来表示边。
	int degree[MAXV];		// 顶点所连接的边数。
};

bool processed[MAXV];
bool discovered[MAXV];
int parent[MAXV];

// 输出最短路径的长度。
int find_path(int start, int target)
{
	int steps = 1;

	while (parent[target] != start)
	{
		steps++;
		target = parent[target];
	}

	return steps;
}

// 使用宽度优先搜索。
int  breadth_first_search(graph * g, int start, int target)
{
	queue < int > q;

	q.push(start);
	discovered[start] = true;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();

		// 遍历与数 v 相邻的数。
		processed[v] = true;
		for (int i = 0; i < g->degree[v]; i++)
		{
			if (discovered[g->edges[v][i]] == false)
			{
				q.push(g->edges[v][i]);
				discovered[g->edges[v][i]] = true;
				parent[g->edges[v][i]] = v;
			}

			// 若未处理则检测是否为目标数。
			if (processed[g->edges[v][i]] == false)
				if (g->edges[v][i] == target)
					return find_path(start, target);
		}
	}
	
	return -1;
}

// 生成与数 current 相连的八个数。
void generate_neighbor(int current, int neighbor[])
{
	int digits[NDIGITS], temp[NDIGITS], count = 0;

	// 将数 current 拆分为数字。
	memset(digits, 0, sizeof(digits));
	while (current)
	{
		digits[count++] = current % NBASE;
		current /= NBASE;
	}

	// 生成相邻数。
	count = 0;
	for (int i = 0; i < MAXDEGREE; i++)
	{
		memcpy(temp, digits, sizeof(digits));

		temp[i / 2] += ((i % 2) ? -1 : 1);
		if (temp[i / 2] >= 0)
			temp[i / 2] %= NBASE;
		else
			temp[i / 2] += NBASE;

		int number = 0;
		for (int j = NDIGITS - 1; j >= 0; j--)
			number = number * NBASE + temp[j];

		neighbor[count++] = number;
	}
}

// 初始化图。
void initialize_graph(graph * g)
{
	// 初始化宽度优先搜索所使用的标记。
	memset(processed, false, sizeof(processed));
	memset(discovered, false, sizeof(discovered));
	memset(parent, -1, sizeof(parent));
	memset(g->degree, 0, sizeof(g->degree));
	
	for (int i = 0; i < MAXV; i++)
	{
		int neighbor[MAXDEGREE];
		generate_neighbor(i, neighbor);
		memcpy(g->edges[i], neighbor, sizeof(neighbor));
		g->degree[i] = MAXDEGREE;
	}
}

bool cmp(int x, int y)
{
	return x > y;
}

// 从图中移除与数 forbidden 相连的边。
void remove_edge(graph * g, int forbidden)
{
	for (int i = 0; i < g->degree[forbidden]; i++)
	{
		int v = g->edges[forbidden][i];
		for (int j = 0; j < g->degree[v]; j++)
			if (g->edges[v][j] == forbidden)
			{
				g->edges[v][j] = 0;
				sort(g->edges[v], g->edges[v] + MAXDEGREE, cmp);
				g->degree[v]--;
				break;
			}
	}
	
	g->degree[forbidden] = 0;
	memset(g->edges[forbidden], 0, MAXDEGREE * sizeof(int));
}

// 将字符串表示的数值转换为整数。
int read(void)
{
	int digit, number = 0;
	
	for (int i = 0; i < NDIGITS; i++)
	{
		cin >> digit;
		number = number * NBASE + digit;
	}

	return number;
}

int main(int ac, char *av[])
{
	int cases, start, target, forbidden, nforbidden;
	graph g;

	cin >> cases;
	while (cases--)
	{
		// 构建图。
		initialize_graph(&g);

		start = read();
		target = read();

		cin >> nforbidden;
		for (int i = 0; i < nforbidden; i++)
		{
			forbidden = read();
			remove_edge(&g, forbidden);
		}

		// 若给定的初始状态和目标状态相同，则不需按动按钮。
		if (start == target)
		{
			cout << "0" << endl;
			continue;
		}

		// 若给定的初始状态数或目标状态数其度为 0，则不可能完成。
		if (g.degree[start] == 0 || g.degree[target] == 0)
		{
			cout << "-1" << endl;
			continue;
		}

		// 使用宽度优先搜索找最短路径长度。
		cout << breadth_first_search(&g, start, target) << endl;
	}

	return 0;
}
