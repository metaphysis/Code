// Crimewave
// UVa ID: 563
// Verdict: Accepted
// Submission Date: 2016-10-13
// UVa Run Time: 0.090s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

const int MAXV = 5100;

map<int, int> arcs[MAXV];
int path[MAXV], visited[MAXV];
int offset[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
int problem, streets, avenues, banks;

bool bfs(int source, int sink)
{
    memset(visited, 0, sizeof(visited));
	memset(path, -1, sizeof(path));

	queue<int> vertices;

	vertices.push(source);
	visited[source] = 1;

	while (!vertices.empty())
	{
		int v = vertices.front();
		vertices.pop();
		for (auto a : arcs[v])
			// 沿着残留容量为正的弧进行图遍历，检查是否为饱和边。
			if (a.second > 0)
				if (!visited[a.first])
				{
					vertices.push(a.first);
					visited[a.first] = 1;
					path[a.first] = v;

					// 遍历到汇点后说明已经找到一条增广路，可以退出。
					if (a.first == sink)
						return true;
				}
	}

	return false;
}

void augmentPath(int source, int sink)
{
	if (source == sink) return;
	arcs[path[sink]][sink] = 0;
	arcs[sink][path[sink]] = 1;
	augmentPath(source, path[sink]);
}

int edmondsKarp()
{
	int maxFlow = 0, source = 0, sink = 5010;
	while (bfs(source, sink))
	{
		maxFlow++;
		augmentPath(source, sink);
	}
	return maxFlow;
}

void buildGraph()
{
    for (int i = 0; i < 5100; i++)
        arcs[i].clear();

    // 在源点和银行之间建立有向弧。
    for (int b = 1, x, y; b <= banks; b++)
    {
        cin >> x >> y;
        arcs[0][(x - 1) * avenues + y] = 1;
        arcs[(x - 1) * avenues + y][0] = 0;
    }
    
    int base = streets * avenues;
    for (int s = 1; s <= streets; s++)
        for (int a = 1; a <= avenues; a++)
        {
            int index = (s - 1) * avenues + a;
            
            // 在城镇边界上的交叉路口和汇点之间建立有向弧。
            if (s == 1 || s == streets || a == 1 || a == avenues)
            {
                arcs[base + index][5010] = 1;
                arcs[5010][base + index] = 0;
            }
                
            // 将交叉路口拆分为两个顶点，在顶点间构建残留网络。
            arcs[index][base + index] = 1;
            arcs[base + index][index] = 0;
                    
            for (int f = 0; f < 4; f++)
            {
                int ss = s + offset[f][0], aa = a + offset[f][1];
                if (ss >= 1 && ss <= streets && aa >= 1 && aa <= avenues)
                {
                    arcs[base + index][(ss - 1) * avenues + aa] = 1;
                    arcs[(ss - 1) * avenues + aa][base + index] = 0;
                    
                    //arcs[base + (ss - 1) * avenues + aa][index] = 1;
                    //arcs[index][base + (ss - 1) * avenues + aa] = 0;
                }
            }
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    cin >> problem;
    for (int p = 1; p <= problem; p++)
    {
        cin >> streets >> avenues >> banks;
        buildGraph();
        bool possible = edmondsKarp() == banks;
        cout << (possible ? "possible" : "not possible") << '\n';
    }
    
	return 0;
}
