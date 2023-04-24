// Numbering the Paths
// UVa ID: 10544
// Verdict: Accepted
// Submission Date: 2023-04-24
// UVa Run Time: 0.280s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> g[26];

int dfs(int u) {
    int r = g[u].size() ? 0 : 1;
    for (auto v : g[u])
        r += dfs(v);
    return r;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases, n, m;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) g[i].clear();
        for (int i = 0; i < m; i++) {
            char u, v;
            cin >> u >> v;
            g[u - 'A'].push_back(v - 'A');
        }
        for (int i = 0; i < n; i++) {
            sort(g[i].begin(), g[i].end());
            g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
        }
        int c[26];
        for (int i = 0; i < n; i++) c[i] = dfs(i);
        int q;
        cin >> q;
        string path;
        for (int i = 0; i < q; i++) {
            cin >> path;
            int r = 1;
            for (int j = 0; j < path.size() - 1; j++) {
                for (auto v : g[path[j] - 'A'])
                    if (v < path[j + 1] - 'A')
                        r += c[v];
            }
            cout << path << ": " << r << '\n';
        }
    }
    return 0;
}
