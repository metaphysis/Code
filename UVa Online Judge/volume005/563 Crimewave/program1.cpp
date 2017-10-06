// Crimewave
// UVa ID: 563
// Verdict: Accepted
// Submission Date: 2017-09-21
// UVa Run Time: 0.070s
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

const int MAXV = 5100, MAXA = 31000, INF = 0x7fffffff;

struct arc
{
    int u, v, capacity, residual, next;
};

class EdmondsKarp
{
private:
    arc *arcs;
    int vertices, idx, source, sink, *head, *path, *visited;

public:
    EdmondsKarp(int v, int e, int s, int t)
    {
        vertices = v;
        head = new int[v], path = new int[v], visited = new int[v];
        arcs = new arc[e];
        source = s, sink = t;
        idx = 0;
        memset(head, 0xff, vertices * sizeof(int));
    }

    ~EdmondsKarp()
    {
        delete [] head, path, visited, arcs;
    }
    
    int maxFlow()
    {
        int flow = 0;

        while (true)
        {
            memset(path, -1, vertices * sizeof(int));
            memset(visited, 0, vertices * sizeof(int));

            queue<int> unvisited; unvisited.push(source);
            visited[source] = 1;

            while (!unvisited.empty())
            {
                int u = unvisited.front(); unvisited.pop();

                for (int x = head[u]; x != -1; x = arcs[x].next)
                    if (!visited[arcs[x].v] && arcs[x].residual > 0)
                    {
                        unvisited.push(arcs[x].v);
                        visited[arcs[x].v] = 1;
                        path[arcs[x].v] = x;
                    }
            }

            if (!visited[sink]) break;

            int delta = INF;
            for (int x = path[sink]; x != -1; x = path[arcs[x].u])
                delta = min(delta, arcs[x].residual);
            flow += delta;
            for (int x = path[sink]; x != -1; x = path[arcs[x].u])
            {
                arcs[x].residual -= delta;
                arcs[x ^ 1].residual += delta;
            }
        }

        return flow;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[idx] = (arc){u, v, capacity, capacity, head[u]};
        head[u] = idx++;
        arcs[idx] = (arc){v, u, capacity, 0, head[v]};
        head[v] = idx++;
    }
};

int problem, streets, avenues, banks;

void createGraph(EdmondsKarp &ek)
{
    // 上下左右四个顶点的坐标偏移量。
    int offset[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

    // 在源点和银行之间建立有向弧。
    for (int b = 1, x, y; b <= banks; b++)
    {
        cin >> x >> y;
        ek.addArc(0, (x - 1) * avenues + y, 1);
    }

    // 在交叉路口之间和交叉路口与汇点间建立有向弧。
    int base = streets * avenues;
    for (int s = 1; s <= streets; s++)
        for (int a = 1; a <= avenues; a++)
        {
            int index = (s - 1) * avenues + a;

            // 将交叉路口拆分为前点和后点并建立有向弧。
            ek.addArc(index, base + index, 1);

            // 如果交叉路口不位于城镇的边界上，则每个交叉路口的后点向上下左右四个
            // 交叉路口的前点建立有向弧，否则在交叉路口的后点和汇点间建立有向弧。
            if (s > 1 && s < streets && a > 1 && a < avenues)
            {
                for (int f = 0; f < 4; f++)
                {
                    int ss = s + offset[f][0], aa = a + offset[f][1];
                    if (ss >= 1 && ss <= streets && aa >= 1 && aa <= avenues)
                        ek.addArc(base + index, (ss - 1) * avenues + aa, 1);
                }
            }
            else
                ek.addArc(base + index, 2 * streets * avenues + 1, 1);
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> problem;
    for (int p = 1; p <= problem; p++)
    {
        cin >> streets >> avenues >> banks;
        EdmondsKarp ek(MAXV, MAXA, 0, 2 * streets * avenues + 1);
        createGraph(ek);
        cout << (ek.maxFlow() == banks ? "possible" : "not possible") << '\n';
    }

    return 0;
}
