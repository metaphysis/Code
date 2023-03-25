// Weak Links
// UVa ID: 12783
// Verdict: Accepted
// Submission Date: 2023-03-25
// UVa Run Time: 0.160s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 2010;

struct edge {
    int start, end;
    bool operator<(const edge &x) const {
        if (start != x.start) return start < x.start;
        else return end < x.end;
    }
};

vector<int> g[MAXV];
vector<edge> bridge;
int dfn[MAXV], low[MAXV], visited[MAXV];

void dfs(int u, int parent, int depth) {
    visited[u] = 1; dfn[u] = low[u] = depth;
    for (auto v : g[u]) {
        if (v != parent && visited[v] == 1) low[u] = min(low[u], dfn[v]);
        if (!visited[v]) {
            dfs(v, u, depth + 1);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]) bridge.push_back((edge){u, v});
        }
    }
    visited[u] = 2;
}

int main(int argc, char *argv[]) {
    int n, m;
    while (cin >> n >> m, n) {
        for (int i = 0; i < n; i++)
            g[i].clear();
        for (int i = 1, u, v; i <= m; i++) {
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        bridge.clear();
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(visited, 0, sizeof(visited));
        for (int u = 0; u < n; u++)
            if (!visited[u])
                dfs(u, -1, 1);
        for (int i = 0; i < bridge.size(); i++)
            if (bridge[i].start > bridge[i].end)
                swap(bridge[i].start, bridge[i].end);
        cout << bridge.size();
        sort(bridge.begin(), bridge.end());
        for (int i = 0; i < bridge.size(); i++)
            cout << ' ' << bridge[i].start << ' ' << bridge[i].end;
        cout << '\n';
    }
	return 0;
}
