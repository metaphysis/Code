// One-way traffic
// UVa ID: 1310
// Verdict: Accepted
// Submission Date: 2016-08-31
// UVa Run Time: 0.750s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_V = 2010;

struct edge
{
    int start, end;
};

vector<int> way[MAX_V];
vector<edge> bridge;
int dfn[MAX_V], low[MAX_V], visited[MAX_V];

void dfs(int u, int parent, int depth)
{
    visited[u] = 1;
    dfn[u] = low[u] = depth;
    for (auto v : way[u])
    {
        if (v != parent && visited[v] == 1)
            low[u] = min(low[u], dfn[v]);
        if (!visited[v])
        {
            dfs(v, u, depth + 1);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v])
                bridge.push_back((edge){u, v});
        }
    }
    visited[u] = 2;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, m, from, to, direction = 0;
    while (cin >> n >> m)
    {
        for (int i = 1; i <= n; i++)
            way[i].clear();

        for (int i = 1; i <= m; i++)
        {
            cin >> from >> to >> direction;
            way[from].push_back(to);
            way[to].push_back(from);
        }
        
        for (int u = 1; u <= n; u++)
        {
            memset(dfn, 0, sizeof(dfn));
            memset(low, 0, sizeof(low));
            memset(visited, 0, sizeof(visited));
            bridge.clear();
            
            dfs(u, -1, 1);
            
            for (int i = 0; i < bridge.size(); i++)
                cout << bridge[i].start << ' ' << bridge[i].end << '\n';
        }
    }
    
	return 0;
}
