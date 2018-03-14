// Roads in the North
// UVa ID: 10308
// Verdict: Accepted
// Submission Date: 2018-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10010;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
};

list<edge> edges[MAXV];
int s, t, maxD, visited[MAXV];

void dfs(int u, int d)
{
    if (d > maxD)
    {
        maxD = d;
        t = u;
    }

    visited[u] = 1;
    for (auto e1 : edges[u])
        if (!visited[e1.v])
            dfs(e1.v, d + e1.w);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    istringstream iss;
    int s, u, v, w;

    while (getline(cin, line))
    {
        for (int i = 1; i < MAXV; i++) edges[i].clear();
        do
        {
            iss.clear(); iss.str(line);
            iss >> u >> v >> w;
            edges[u].push_back(edge(v, w));
            edges[v].push_back(edge(u, w));
            s = u;
        } while (getline(cin, line), line.length() > 0);
        
        memset(visited, 0, sizeof(visited));
        maxD = -1;
        dfs(s, 0);
        
        memset(visited, 0, sizeof(visited));
        maxD = -1;
        dfs(t, 0);
        
        cout << maxD << '\n';
    }

    return 0;
}
