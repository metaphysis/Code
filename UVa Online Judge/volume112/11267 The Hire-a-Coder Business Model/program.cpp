// The Hire-a-Coder Business Model
// UVa ID: 11267
// Verdict: Accepted
// Submission Date: 2019-01-04
// UVa Run Time: 0.020s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 210, MAXE = 12000;

struct edge {
    int u, v, weight;
    edge (int u = 0, int v = 0, int weight = 0): u(u), v(v), weight(weight) {}
    bool operator<(const edge &e) const { return weight < e.weight; }
} edges[MAXE];

list<int> graph[MAXV];

int cntOfVertices, cntOfEdges;

// 连通图以及二分图检测。
const int BLACK = 1, WHITE = 2;

int color[MAXV], fail = 0;

void dfs(int u, int c)
{
    if (fail) return;
    color[u] = c;
    for (auto v : graph[u])
        if (!color[v])
            dfs(v, 3 - c);
        else
        {
            if (color[v] != 3 - c)
            {
                fail = 1;
                return;
            }
        }
}

int parent[MAXV], ranks[MAXV];

void makeSet()
{
    for (int i = 0; i < cntOfVertices; i++) parent[i] = i, ranks[i] = 0;
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

bool unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
        return true;
    }
    return false;
}

int kruskal()
{
    int sumOfWeight = 0;

    makeSet();
    sort(edges, edges + cntOfEdges);

    for (int i = 0; i < cntOfEdges; i++)
        if (unionSet(edges[i].u, edges[i].v) || edges[i].weight < 0)
            sumOfWeight += edges[i].weight;
    return sumOfWeight;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> cntOfVertices)
    {
        if (cntOfVertices == 0) break;
        for (int v = 0; v < cntOfVertices; v++)
            graph[v].clear();
        cin >> cntOfEdges;
        for (int e = 0, u, v, weight; e < cntOfEdges; e++)
        {
            cin >> u >> v >> weight;
            u--, v--;
            edges[e] = edge(u, v, weight);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        memset(color, 0, sizeof(color));
        fail = 0;
        dfs(0, BLACK);
        for (int v = 0; v < cntOfVertices; v++)
            if (!color[v])
            {
                fail = 1;
                break;
            }
        if (fail)
            cout << "Invalid data, Idiot!\n";
        else
            cout << kruskal() << '\n';
    }

    return 0;
}
