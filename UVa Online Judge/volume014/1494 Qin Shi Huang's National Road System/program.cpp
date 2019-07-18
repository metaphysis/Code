// Qin Shi Huang's National Road System
// UVa ID: 1494
// Verdict: Accepted
// Submission Date: 2019-07-18
// UVa Run Time: 0.100s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, MAXE = 1000010;

struct edge
{
    int u, v, next;
    double cost;
    bool operator<(const edge& e) const { return cost < e.cost; }
};

edge edges[MAXE], g[2 * MAXV];
int idx, head[MAXV], parent[MAXV];
int n, X[MAXV], Y[MAXV], P[MAXV], visited[MAXV];
double maxCost[MAXV][MAXV];

double getDist(int i, int j)
{
    return sqrt((X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]));
}

int findSet(int x)
{
    return x == parent[x] ? x : (parent[x] = findSet(parent[x]));
}

double kruskal()
{
    int tot = idx;
    for (int i = 0; i < n; i++) parent[i] = i;
    idx = 0;
    memset(head, -1, sizeof(head));
    double mst = 0;
    sort(edges, edges + tot);
    for (int i = 0; i < tot; i++)
        if (findSet(edges[i].u) != findSet(edges[i].v))
        {
            int u = edges[i].u, v = edges[i].v;
            mst += edges[i].cost;
            parent[findSet(u)] = findSet(v);
            g[idx] = edge{u, v, head[u], edges[i].cost};
            head[u] = idx++;
            g[idx] = edge{v, u, head[v], edges[i].cost};
            head[v] = idx++;
        }
    return mst;
}

void dfs(int root, int x)
{
    visited[x] = 1;
    for (int i = head[x]; ~i; i = g[i].next)
        if (!visited[g[i].v])
        {
            maxCost[root][g[i].v] = max(maxCost[root][g[i].u], g[i].cost);
            dfs(root, g[i].v);
        }
}

int main(int argc, char *argv[])
{
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> X[i] >> Y[i] >> P[i];
        idx = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                edges[idx++] = edge{i, j, 0, getDist(i, j)};
        double mst = kruskal();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                maxCost[i][j] = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) visited[j] = 0;
            dfs(i, i);
        }
        double rate = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                rate = max(rate, (P[i] + P[j]) / (mst - maxCost[i][j]));
        cout << fixed << setprecision(2) << rate << '\n';
    }
    return 0;
}
