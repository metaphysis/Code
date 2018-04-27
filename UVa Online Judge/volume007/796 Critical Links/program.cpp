// Critical Links
// UVa ID: 796
// Verdict: Accepted
// Submission Date: 2016-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 2010;

struct edge
{
    int start, end;

    bool operator<(const edge &x) const
    {
        if (start != x.start)
            return start < x.start;
        else
            return end < x.end;
    }
};

vector<int> edges[MAXV];
vector<edge> bridge;
int dfn[MAXV], low[MAXV], visited[MAXV];

void dfs(int u, int parent, int depth)
{
    visited[u] = 1; dfn[u] = low[u] = depth;
    for (auto v : edges[u])
    {
        if (v != parent && visited[v] == 1) low[u] = min(low[u], dfn[v]);
        if (!visited[v])
        {
            dfs(v, u, depth + 1);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]) bridge.push_back((edge){u, v});
        }
    }
    visited[u] = 2;
}

int main(int argc, char *argv[])
{
    int servers;
    while (cin >> servers)
    {
        for (int i = 0; i < servers; i++)
            edges[i].clear();

        string text;
        int from, to, connections;
        for (int i = 1; i <= servers; i++)
        {
            cin >> from >> text;
            
            connections = stoi(text.substr(1, text.length() - 2));
            for (int j = 1; j <= connections; j++)
            {
                cin >> to;
                edges[from].push_back(to);
                edges[to].push_back(from);
            }
        }

        bridge.clear();
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(visited, 0, sizeof(visited));

        for (int u = 0; u < servers; u++)
            if (!visited[u])
                dfs(u, -1, 1);

        for (int i = 0; i < bridge.size(); i++)
            if (bridge[i].start > bridge[i].end)
                swap(bridge[i].start, bridge[i].end);

        cout << bridge.size() << " critical links\n";
        sort(bridge.begin(), bridge.end());
        for (int i = 0; i < bridge.size(); i++)
            cout << bridge[i].start << " - " << bridge[i].end << '\n';

        cout << '\n';
    }

	return 0;
}
