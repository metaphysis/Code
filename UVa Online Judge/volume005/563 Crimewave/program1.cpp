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

const int MAXV = 5100, MAXA = 31000;

struct arc
{
    int u, v, capacity, flow, residual, next;
};

arc arcs[MAXA];
int source, sink, path[MAXV], visited[MAXV];

int edmondsKarp()
{
    int flows = 0;

	while (true)
	{
	    // 使用广度优先遍历寻找从源点到汇点的增广路。
        memset(visited, 0, sizeof(visited));
	    memset(path, -1, sizeof(path));

	    queue<int> unvisited;
	    unvisited.push(source);
	    visited[source] = 1;

	    while (!unvisited.empty())
	    {
		    int x = unvisited.front();
		    unvisited.pop();
		    
		    // 遍历以当前顶点为起点的有向弧，沿着残留容量为正的弧进行图遍历。
		    for (; x != -1; x = arcs[x].next)
			    if (!visited[arcs[x].v] && arcs[x].residual > 0)
			    {
				    unvisited.push(arcs[x].v);
				    visited[arcs[x].v] = 1;
				    path[arcs[x].v] = u;
			    }
	    }
	    
	    // 遍历未能到达汇点，表明不存在增广路。
	    if (!visited[sink])
	        break;

	    int flow = arcs[x].residual;
        for (x = path[x]; x != -1; x = path[x])
            flow = min(flow, arcs[x].residual);
        
        // 更新可行流的流量及残留网络。
        flows += flow[sink];

        for (int x = sink; x != -1; x = path[x])
        {
            arcs[x].flow += flow[sink];
            arcs[x].residual -= flow[sink];
            arcs[x ^ 1].residual += flow[sink];
        }
	}

	return flows;
}

int problem, streets, avenues, banks, indexer, last[MAXV];

void addArc(int u, int v, int capacity)
{
    arcs[indexer].u = u, arcs[indexer].v = v;
    arcs[indexer].capacity = capacity, arcs[indexer].flow = 0;
    arcs[indexer].residual = capacity, arcs[indexer].next = -1;
    arcs[last[u]].next = indexer, last[u] = indexer++;
    
    arcs[indexer].u = v, arcs[indexer].v = u;
    arcs[indexer].capacity = capacity, arcs[indexer].flow = 0;
    arcs[indexer].residual = 0, arcs[indexer].next = -1;
    arcs[last[v]].next = indexer, last[v] = indexer++;
}

void buildGraph()
{
    // 上下左右四个顶点的坐标偏移量。
    int offset[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    
    // 初始化有向弧计数器，源点和汇点编号，顶点在链表中的最后序号。
    indexer = 0, source = 0, sink = 2 * streets * avenues + 1;
    memset(last, 0, sizeof(last));
    
    // 在源点和银行之间建立有向弧。
    for (int b = 1, x, y; b <= banks; b++)
    {
        cin >> x >> y;
        addArc(source, (x - 1) * avenues + y, 1);
    }

    // 在交叉路口之间和交叉路口与汇点间建立有向弧。
    int base = streets * avenues;
    for (int s = 1; s <= streets; s++)
        for (int a = 1; a <= avenues; a++)
        {
            int index = (s - 1) * avenues + a;
 
            // 将交叉路口拆分为前点和后点并建立有向弧。
            addArc(index, base + index, 1);

            // 如果交叉路口不位于城镇的边界上，则每个交叉路口的后点向上下左右四个
            // 交叉路口的前点建立有向弧，否则在交叉路口的后点和汇点间建立有向弧。
            if (s > 1 && s < streets && a > 1 && a < avenues)
            {
                for (int f = 0; f < 4; f++)
                {
                    int ss = s + offset[f][0], aa = a + offset[f][1];
                    if (ss >= 1 && ss <= streets && aa >= 1 && aa <= avenues)
                        addArc(base + index, (ss - 1) * avenues + aa, 1);
                }
            }
            else
                addArc(base + index, sink, 1);
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
        bool possible = (edmondsKarp() == banks);
        cout << (possible ? "possible" : "not possible") << '\n';
    }

	return 0;
}
