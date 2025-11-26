// Caves
// UVa ID: 1407
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 505;

vector<pair<int, int>> graph[MAXN];
int dp[MAXN][MAXN], f[MAXN][MAXN];
int size[MAXN];
int n, q;

void dfs(int u) {
    size[u] = 1;
    dp[u][1] = f[u][1] = 0;
    for (auto& edge : graph[u]) {
        int v = edge.first, w = edge.second;
        dfs(v);
        for (int i = size[u]; i >= 1; --i) {
            for (int j = 1; j <= size[v]; ++j) {
                dp[u][i + j] = min(dp[u][i + j], dp[u][i] + dp[v][j] + 2 * w);
                f[u][i + j] = min(f[u][i + j], min(f[u][i] + dp[v][j] + 2 * w, dp[u][i] + f[v][j] + w));
            }
        }
        size[u] += size[v];
    }
}

int main() {
    int caseNum = 1;
    while (cin >> n, n) {
        for (int i = 0; i < n; ++i) graph[i].clear();
        for (int i = 0; i < n - 1; ++i) {
            int a, b, d;
            cin >> a >> b >> d;
            graph[b].push_back({a, d});
        }
        memset(dp, 0x3f, sizeof dp);
        memset(f, 0x3f, sizeof f);
        dfs(0);
        cin >> q;
        cout << "Case " << caseNum++ << ":" << endl;
        while (q--) {
            int x;
            cin >> x;
            int ans = 1;
            for (int k = n; k >= 1; --k) {
                if (min(dp[0][k], f[0][k]) <= x) {
                    ans = k;
                    break;
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}
