// Cactus
// UVa ID: 10510
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, m, flag;
vector<int> g[10010];
int visited[10010], in[10010], out[10010], cnt[10010], parent[10010];

void dfs(int u, int father) {
    visited[u] = 1;
    parent[u] = father;
    for (auto v : g[u])
        if (!visited[v]) dfs(v, u);
        else {
            int p = parent[u];
            while (p != v) {
                cnt[p]++;
                if (cnt[p] >= 2) {
                    flag = 0;
                    return;
                }
                p = parent[p];
            }
        }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    while (cases--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            g[i].clear();
            visited[i] = in[i] = out[i] = 0;
        }
        for (int i = 0, u, v; i < m; i++) {
            cin >> u >> v;
            g[u].push_back(v);
            out[u]++, in[v]++;
        }
        flag = 1;
        dfs(0, -1);
        for (int i = 0; i < n; i++)
            if (!visited[i]) {
                flag = 0;
                break;
            }
        for (int i = 0; i < n; i++)
            if (in[i] != out[i]) {
                flag = 0;
                break;
            }
        cout << (flag ? "YES" : "NO") << '\n';
    }
    return 0;
}
