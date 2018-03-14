// The Necklace （项链）
// PC/UVa IDs: 111002/10054, Popularity: B, Success rate: low Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-04
// UVa Run Time: 0.556s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [Problem Description]
// My little sister had a beautiful necklace made of colorful beads. Each two
// successive beads in the necklace shared a common color at their meeting point,
// as shown below:
//
//    ----green--red----red--white----white--green----green--blue----
//
// But, alas! One day, the necklace tore and the beads were scattered all over the
// floor. My sister did her best to pick up all the beads, but she is not sure
// whether she found them all. Now she has come to me for help. She wants to know
// whether it is possible to make a necklace using all the beads she has in the
// same way that her original necklace was made. If so, how can the beads be so
// arranged?
//
// Write a program to solve the problem.
//
// [Input]
// The first line of the input contains the integer T , giving the number of test
// cases. The first line of each test case contains an integer N (5 ≤ N ≤ 1,000)
// giving the number of beads my sister found. Each of the next N lines contains
// two integers describing the colors of a bead. Colors are represented by integers
// ranging from 1 to 50.
//
// [Output]
// For each test case, print the test case number as shown in the sample output.
// If reconstruction is impossible, print the sentence “some beads may be lost”
// on a line by itself. Otherwise, print N lines, each with a single bead description
// such that for 1 ≤ i ≤ N − 1, the second integer on line i must be the same as
// the first integer on line i + 1. Additionally, the second integer on line N
// must be equal to the first integer on line 1. There may be many solutions, any
// one of which is acceptable.
//
// Print a blank line between two successive test cases.
//
// [Sample Input]
// 2
// 5
// 1 2
// 2 3
// 3 4
// 4 5
// 5 6
// 5
// 2 1
// 2 2
// 3 4
// 3 1
// 2 4
//
// [Sample Output]
// Case #1
// some beads may be lost
//
// Case #2
// 2 1
// 1 3
// 3 4
// 4 2
// 2 2
//
// [解题方法]
// 若把珠子两端的颜色看作是顶点，珠子本身看成是边，则该题可以建模成欧拉回路问题。
// 需要判断顶点的度是否为都为偶数，若都为偶数才可能包含欧拉回路，然后判断图是否
// 连通，若这两个条件都满足，则肯定存在欧拉回路，找出即可。使用宽度或深度优先遍
// 历确定图的连通性，亦可考虑使用不相交集合并/查数据结构（并查集）来实现判断。
// 由于本题有较多的输入输出，在输出换行时，使用 “\n" 而不是 endl 可以减少一些
// 运行时间（使用 endl 时运行时间为 1.668s，因为 endl 在输出换行符后都要立即刷
// 新输出缓存，故耗费较多时间）。在提交中还发现，UVa OnlineJudge 中的测试数据都
// 是连通图，判断是否为连通图的一步其实可以省略掉！呵，测试数据还真是较弱......

#include <bits/stdc++.h>

using namespace std;

#define MAXV 50

vector<int> edges[MAXV + 1];
int connected[MAXV + 1][MAXV + 1];
int degree[MAXV + 1];
int parent[MAXV + 1];

// 并/查集合的查操作，采用了路径压缩优化。
int find(int x)
{
	return (parent[x] == x) ? x : (parent[x] = find(parent[x]));
}

// 输出欧拉回路，思路是先找出一个环，然后将此环从图中删除，继续从下一个起点开始
// 找环，将这些环在公共端点连接起来即构成一条欧拉回路。可以使用递归来实现。
void eulerian_cycle(int begin)
{
	for (int to = 1; to <= MAXV; to++)
		if (connected[begin][to])
		{
			connected[begin][to]--;
			connected[to][begin]--;
			
			eulerian_cycle(to);

			cout << to << " " << begin << "\n";
		}
}

// 使用宽度优先遍历来判断图是否连通。
bool breadth_first_search(int begin)
{
	bool discovered[MAXV + 1];

	// 边数为 0 表示该颜色未出现，标记为已遍历。
	for (int c = 1; c <= MAXV; c++)
		discovered[c] = (edges[c].size() == 0);
	
	queue < int > q;
	q.push(begin);
	
	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();
		
		for (int v = 0; v < edges[vertex].size(); v++)
			if (discovered[edges[vertex][v]] == false)
			{
				q.push(edges[vertex][v]);
				discovered[edges[vertex][v]] = true;
			}
	}
	
	// 尚有未发现的顶点，则图不连通。
	for (int c = 1; c <= MAXV; c++)
		if (discovered[c] == false)
			return true;
	
	return false;
}

void solve_by_breadth_first_search(void)
{
	int output = 1, cases;	// 当前测试序号和测试例数。
	int n;			// 珠子数。
	int cleft, cright;	// 珠子左右两端的颜色。

	cin >> cases;
	while (cases--)
	{
		memset(connected, 0, sizeof(connected));
		
		for (int c = 1; c <= MAXV; c++)
			edges[c].clear();

		// 建模成无向图，求欧拉回路。
		cin >> n;
		for (int c = 1; c <= n; c++)
		{
			cin >> cleft >> cright;

			edges[cleft].push_back(cright);
			edges[cright].push_back(cleft);
			
			connected[cleft][cright]++;
			connected[cright][cleft]++;
		}

		// 判断是否为连通图，通过一次宽度优先遍历即可确定。找一个起点进行遍历。
		int begin = 1;
		while (!edges[begin].size())
			begin++;

		bool impossible = breadth_first_search(begin);

		// 若图可连通则判断度是否都为偶数。
		if (!impossible)
		{
			for (int c = 1; c <= MAXV; c++)
				if (edges[c].size() & 1)
				{
					impossible = true;
					break;
				}
		}
		
		cout << "Case #" << output++ << "\n";
		if (impossible)
			cout << "some beads may be lost\n" << endl;
		else
			eulerian_cycle(begin);
		
		if (cases)
			cout << "\n";
	}
}

// 使用并查集解题。
void solve_by_union_find(void)
{
	int output = 1, cases;	// 当前测试序号和测试例数。
	int n;			// 珠子数。
	int cleft, cright;	// 珠子左右两端的颜色。
	
	cin >> cases;
	while (cases--)
	{
		memset(connected, 0, sizeof(connected));
		memset(degree, 0, sizeof(degree));
		
		for (int c = 1; c <= MAXV; c++)
			parent[c] = c;

		cin >> n;
		for (int c = 1; c <= n; c++)
		{
			cin >> cleft >> cright;

			connected[cleft][cright]++;
			connected[cright][cleft]++;
			
			degree[cleft]++;
			degree[cright]++;
			
			// 查找 cleft 和 cright 是否位于同一集合，若不位于同一集合，则执行
			// 并操作。
			int pleft = find(cleft);
			int pright = find(cright);

			if (pleft != pright)
				parent[pleft] = pright; 
		}
		
		
		bool impossible = false;

		// 判断是否为连通图，先找到一个度不为 0 的顶点作为起始。
		int begin = 1;
		while (!degree[begin])
			begin++;

		int tparent = find(begin);
		for (int c = 1 + begin; c <= MAXV; c++)
			if (degree[c] && find(c) != tparent)
			{
				impossible = true;
				break;
			}
		
		// 判断顶点的度数是否都为偶数。
		if (!impossible)
		{
			for (int c = 1; c <= MAXV; c++)
				if (degree[c] & 1)
				{
					impossible = true;
					break;
				}
		}
		
		cout << "Case #" << output++ << "\n";

		if (impossible)
			cout << "some beads may be lost\n";
		else
			eulerian_cycle(begin);
				
		if (cases)
			cout << "\n";
	}
}

int main(int ac, char *av[])
{
	// 使用宽度优先遍历判断图是否连通，UVa RT 0.556s。
	solve_by_breadth_first_search();
	
	// 使用并查集判断图是否连通，UVa RT 0.560s。
	// solve_by_union_find();

	return 0;
}
