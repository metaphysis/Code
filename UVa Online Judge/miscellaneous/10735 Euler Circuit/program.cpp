// Euler Circuit
// UVa ID: 10735
// Verdict: Accepted
// Submission Date: 2017-09-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int INF = 0x7fffffff;

int V, E;
vector<int> edges[210];
        
class DisjointSet
{
  private:
    int vertices, *parent, *rank;

  public:
    DisjointSet(int v)
    {
        vertices = v;
        parent = new int[v], rank = new int[v];
        makeSet();
    }

    ~DisjointSet()
    {
        delete [] parent, rank;
    }

    void makeSet()
    {
        for (int i = 0; i < vertices; i++)
            parent[i] = i, rank[i] = 0;
    }

    int findSet(int x)
    {
        return (x == parent[x] ? x : parent[x] = findSet(parent[x]));
    }

    bool unionSet(int x, int y)
    {
        x = findSet(x), y = findSet(y);
        if (x != y)
        {
            if (rank[x] > rank[y])
                parent[y] = x;
            else
            {
                parent[x] = y;
                if (rank[x] == rank[y])
                    rank[x]++;
            }
            return true;
        }
        return false;
    }
};

struct arc
{
    int u, v, capacity, residual, next;
};

class EdmondsKarp
{
private:
    arc *arcs;
    int vertices, indexer, source, sink, *link, *parent, *visited;

public:
    EdmondsKarp(int v, int e, int s, int t)
    {
        vertices = v, indexer = 0, source = s, sink = t;
        link = new int[v], parent = new int[v], visited = new int[v];
        arcs = new arc[e];
        for (int i = 0; i < v; i++) link[i] = -1;
    }

    ~EdmondsKarp()
    {
        delete [] link, parent, visited, arcs;
    }
    
    int maxFlow()
    {
        int netFlow = 0;

        while (true)
        {
            // 使用广度优先遍历寻找从源点到汇点的增广路。
            for (int i = 0; i < vertices; i++) visited[i] = 0, parent[i] = -1;

            queue<int> unvisited;
            unvisited.push(source);
            visited[source] = 1;

            while (!unvisited.empty())
            {
                int u = unvisited.front();
                unvisited.pop();

                // 遍历以当前顶点为起点的有向弧，沿着残留容量为正的弧进行图遍历。
                for (int x = link[u]; x != -1; x = arcs[x].next)
                    if (!visited[arcs[x].v] && arcs[x].residual > 0)
                    {
                        unvisited.push(arcs[x].v);
                        visited[arcs[x].v] = 1;

                        // 注意路径记录的是有向弧的编号。
                        parent[arcs[x].v] = x;
                    }
            }

            // 遍历未能到达汇点，表明不存在增广路，当前可行流已经为最大流。
            if (!visited[sink]) break;

            // 确定增广路的流量。
            int delta = INF;
            for (int x = parent[sink]; x != -1; x = parent[arcs[x].u])
                delta = min(delta, arcs[x].residual);

            // 更新可行流的流量及残留网络。
            netFlow += delta;

            for (int x = parent[sink]; x != -1; x = parent[arcs[x].u])
            {
                arcs[x].residual -= delta;
                arcs[x ^ 1].residual += delta;
            }
        }

        return netFlow;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[indexer] = (arc){u, v, capacity, capacity, link[u]};
        link[u] = indexer++;

        arcs[indexer] = (arc){v, u, capacity, 0, link[v]};
        link[v] = indexer++;
    }
    
    vector<arc> getArcs()
    {
        vector<arc> even;
        for (int i = 0; i < indexer; i += 2)
            even.push_back(arcs[i]);
        return even;
    }
};

// Hierholzer algorithm.
void hierholzer()
{
    stack<int> parent;
    vector<int> circuit;

    parent.push(1);
    int current = 1;

    while (!parent.empty())
    {
        if (edges[current].size())
        {
            parent.push(current);
            int next = edges[current].front();
            edges[current].erase(edges[current].begin());
            current = next;
        }
        else
        {
            circuit.push_back(current);
            current = parent.top();
            parent.pop();
        }
    }

    for (int i = circuit.size() - 1; i >= 0; i--)
    {
        cout << circuit[i];
        if (i) cout << ' ';
    }
    cout << '\n';
}
        
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for (int c = 0; c < cases; c++)
    {
        if (c) cout << '\n';

        cin >> V >> E;

        for (int i = 1; i <= V; i++)
            edges[i].clear();

        int a, b;
        char type;

        DisjointSet ds(V + 1);
        EdmondsKarp ek(V + 2, (V + 2) * (V + 2), 0, V + 1);
        int degree[V + 1] = { 0 }, flows = 0, combined = 0;

        for (int i = 1; i <= E; i++)
        {
            cin >> a >> b >> type;

            if (ds.unionSet(a, b)) combined++;

            degree[a]++, degree[b]--;

            if (type == 'D')
                edges[a].push_back(b);
            else
                ek.addArc(a, b, 1);
        }

        // Is the base graph connected?
        bool eulerian = (combined == (V - 1));

        // Is the degree of every vertex even?
        if (eulerian)
        {
            for (int i = 1; i <= V; i++)
            {
                if (abs(degree[i]) & 1)
                {
                    eulerian = false;
                    break;
                }
                
                if (degree[i] > 0)
                {
                    flows += degree[i] / 2;
                    ek.addArc(0, i, degree[i] / 2);
                }
                else
                    ek.addArc(i, V + 1, -degree[i] / 2);
            }
        }

        // Can the network reach max flow?
        if (eulerian)
        {
            eulerian = (ek.maxFlow() == flows);
            if (eulerian)
            {
                for (auto a : ek.getArcs())
                {
                    if (a.u == 0 || a.v == V + 1) continue;

                    if (a.capacity == 1)
                    {
                        if (a.residual == 1)
                            edges[a.u].push_back(a.v);
                        else
                            edges[a.v].push_back(a.u);
                    }
                }
            }
        }

        if (!eulerian)
        {
            cout << "No euler circuit exist\n";
            continue;
        }

        hierholzer();
    }

    return 0;
}
