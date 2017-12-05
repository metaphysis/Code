// Doublets （Doublets 序列）
// PC/UVa IDs: 110307/10150, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-05-20
// UVa Run Time: 0.200s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <queue>
#include <cstring>
	
using namespace std;
	
#define MAXSIZE 25143		// 字典最大数量为25143。
	
// 判断两个单词是否组成一对 Doublets。
bool doublets(string &a, string &b)
{
	// 长度不等，不会是 Doublets。
	if (a.length() != b.length())
		return false;
	
	// 寻找两个单词不同的个数。
	int diff = 0;
	for (int i = 0; i < a.length(); i++)
		if (a[i] != b[i])
		{
			diff++;
			if (diff > 1)
				return false;
		}
	
	return diff == 1;
}
	
void no_solution()
{
	cout << "No solution." << endl;
}
	
void find_path(vector < string > &points, int parent[MAXSIZE], int x, int y)
{
	// 根据 parent 数组回溯得到最短路。从终点 y 往回找，如果父节点为 -1 则表示未找到，如
	// 果为起点x则输出此条路径。
	vector < int > path;
	while (parent[y] != x && parent[y] != -1)
	{
		path.push_back(y);
		y = parent[y];
	}
	
	if (parent[y] == -1)
		no_solution();
	else
	{
		path.push_back(y);
		path.push_back(x);
		for (int m = path.size() - 1; m >= 0; m--)
			cout << points[path[m]] << endl;
	}
}
	
// 使用 BFS（宽度优先搜索）查找最短路并输出。
void bfs(vector < vector < int > > &edges, int parent[MAXSIZE], int x, int y)
{
	// 查找序号为 x 到序号为 y 的单词间的最短路径。
	bool discovered[MAXSIZE];
	queue < int > q;
	int v;
	
	memset(discovered, 0, sizeof(discovered));
	memset(parent, -1, sizeof(parent));
	
	q.push(x);
	discovered[x] = true;
	
	// BFS 遍历图直到遍历完毕或找到序号为 y 的单词。
	bool finish = false;
	while (q.size())
	{
		v = q.front();
		q.pop();
		for (int i = 0; i < edges[v].size(); i++)
		{
			if (!discovered[edges[v][i]])
			{
				q.push(edges[v][i]);
				discovered[edges[v][i]] = true;
				parent[edges[v][i]] = v;
				if (edges[v][i] == y)
				{
					finish = true;
					break;
				}
			}
		}

		if (finish)
			return;
	}
}
	
int main(int ac, char *av[])
{
	vector < vector < int > > edges[16];
	vector < string > points[16];
	bool inited[16];
	string line;
	int m, n;
	
	memset(inited, false, sizeof(inited));
	
	// 读入单词字典数据。
	while (getline(cin, line), line.length() > 0)
	{
		m = line.length() - 1;
		points[m].push_back(line);
	}
	
	int cases = 0;
	while (cases++, getline(cin, line))
	{
		istringstream iss(line);
		string a, b;
		iss >> a >> b;
	
		// 输出空行。
		if (cases > 1)
			cout << endl;
	
		// 若单词长度不等，无解。
		if (a.size() != b.size())
		{
			no_solution();
			continue;
		}
	
		// 找到单词 a 和 b 在图中的序数。
		int x = -1, y = -1;
		int m = a.length() - 1;
		
		// 在图中找到单词 a 和 b 的序号。
		for (int i = 0; i < points[m].size(); i++)
		{
		    if (x == -1 && a == points[m][i])
		        x = i;

		    if (y == -1 && b == points[m][i])
		        y = i;

		    if (x != -1 && y != -1)
		        break;
		}
			
		// 未找到。
		if (x == -1 || y == -1)
			no_solution();
		// 找到，但是单词长度均为 1。
		else if (a.length() == 1 && b.length() == 1)
		{
			// 长度均为 1，但两者不同，直接输出。
			if (a != b)
				cout << a << endl << b << endl;
			else
			{
				// 因为所有单词互不相同，故只要找到一个单词，它与x和y均不同即可。
				// 当然必须单词数大于 2 个。
				if (points[0].size() > 2)
				{
					// 因为所有单词互不相同，故只要找到一个序号，它与
					//  x 和 y 均不同即可。当然必须单词数大于 1 个。
					cout << a << endl;
					for (int i = 0; i < points[0].size(); i++)
						if (i != x && i != y)
						{
							cout << points[0][i] << endl;
							break;
						}
					cout << b << endl;
				}
				else
					no_solution();
			}
		}
		else
		{
			// 单词长度为（m + 1）的图尚未构建，则构建。
			if (!inited[m])
			{
				edges[m].resize(points[m].size());
				for (int i = 0; i < points[m].size() - 1; i++)
					for (int j = (i + 1); j < points[m].size(); j++)
						if (doublets(points[m][i], points[m][j]))
						{
							edges[m][i].push_back(j);
							edges[m][j].push_back(i);
						}

				inited[m] = true;
			}
	
			// 两者长度不为 1，但两个单词相同，则只需要查看该单词是否有 Doublets，
			// 有则将单词作为中间输出。
			if (x == y)
			{
				if (edges[m][x].size())
				{
					cout << a << endl;
					cout << points[m][edges[m][x][0]] << endl;
					cout << b << endl;
				}
				else
					no_solution();
			}
			else
			{
				int parent[MAXSIZE];
				
				// 使用 BFS（宽度优先搜索）查找最短路并输出。
				bfs(edges[m], parent, x, y);

				find_path(points[m], parent, x, y);
			}
		}
	}
	
	return 0;
}
