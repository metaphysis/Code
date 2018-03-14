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

set<int> way[MAX_V];
vector<pair<int, int>> bridge;
int visited[MAX_V];

bool dfs(int u, int d)
{
    visited[u] = 1;
    if (u == d) return true;
    for (auto v : way[u])
        if (!visited[v] && dfs(v, d))
            return true;
    return false;
}

bool connected(int u, int v)
{
    memset(visited, 0, sizeof(visited));
    dfs(u, v);
    return visited[v];
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, m, from, to, direction;
    while (cin >> n >> m)
    {
        for (int i = 1; i <= n; i++)
            way[i].clear();
        bridge.clear();
        
        for (int i = 1; i <= m; i++)
        {
            cin >> from >> to >> direction;
            way[from].insert(to);
            if (direction == 2)
            {
                way[to].insert(from);
                bridge.push_back(make_pair(from, to));
            }
        }
        
        for (int i = 0; i < bridge.size(); i++)
        {
            way[bridge[i].first].erase(bridge[i].second);
            if (connected(bridge[i].first, bridge[i].second))
            {
                cout << bridge[i].second << ' ' << bridge[i].first << " 1\n";
                continue;
            }
            else
                way[bridge[i].first].insert(bridge[i].second);
            
            way[bridge[i].second].erase(bridge[i].first);
            if (connected(bridge[i].second, bridge[i].first))
            {
                cout << bridge[i].first << ' ' << bridge[i].second << " 1\n";
                continue;
            }
            else
                way[bridge[i].second].insert(bridge[i].first);
            
            cout << bridge[i].first << ' ' << bridge[i].second << " 2\n";
        }
    }
    
	return 0;
}
