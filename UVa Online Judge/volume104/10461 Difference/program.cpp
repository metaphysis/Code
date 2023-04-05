// Difference
// UVa ID: 10461
// Verdict: Accepted
// Submission Date: 2023-04-05
// UVa Run Time: 0.010s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int v, e, q, days[510], visited[510], sum, idx, d;
vector<int> g[2][510];

void dfs(int u) {
    visited[u] = 1;
    for (auto v : g[idx][u])
        if (!visited[v]) {
            d += days[v];
            dfs(v);
        }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1;
    while (cin >> v >> e, v) {
        sum = 0;
        for (int i = 1; i <= v; i++) {
            cin >> days[i];
            sum += days[i];
            g[0][i].clear();
            g[1][i].clear();
        }
        for (int i = 1, u, v; i <= e; i++) {
            cin >> u >> v;
            g[0][u].push_back(v);
            g[1][v].push_back(u);
        }
        cout << "Case #" << cases++ << ":\n";
        cin >> q;
        for (int i = 1, u; i <= q; i++) {
            cin >> u;
            d = 0;
            for (int i = 1; i <= v; i++) visited[i] = 0;
            idx = 0;
            dfs(u);
            int sd = d;
            d = 0;
            for (int i = 1; i <= v; i++) visited[i] = 0;
            idx = 1;
            dfs(u);
            int ed = d;
            cout << (sum - days[u] - ed) - sd << '\n';
        }
        cout << '\n';
    }
    return 0;
}
