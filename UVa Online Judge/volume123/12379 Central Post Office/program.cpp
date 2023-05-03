// Central Post Office
// UVa ID: 12379
// Verdict: Accepted
// Submission Date: 2023-05-03
// UVa Run Time: 0.100s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
vector<int> g[10010];
int max_u, max_d;
void dfs(int u, int p, int depth) {
    if (depth > max_d) {
        max_d = depth;
        max_u = u;
    }
    for (auto v : g[u])
        if (v != p)
            dfs(v, u, depth + 1);
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        for (int i = 1; i <= N; i++) g[i].clear();
        for (int i = 1, m; i <= N; i++) {
            cin >> m;
            for (int j = 1, v; j <= m; j++) {
                cin >> v;
                g[i].push_back(v);
            }
        }
        max_d = 0, max_u = 1;
        dfs(1, -1, 0);
        dfs(max_u, -1, 0);
        cout << 2 * (N - 1) - max_d << '\n';
    }
    return 0;
}
