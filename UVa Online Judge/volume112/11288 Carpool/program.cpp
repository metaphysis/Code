// Carpool
// UVa ID: 11288
// Verdict: Accepted
// Submission Date: 2024-11-06
// UVa Run Time: 0.020s
//
// 版权所有（C）2024，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, dist[20][20];
int group, cost, cnt[8], mask[8];
int dp[16][1 << 17];

int dfs2(int u, int bit) {
    if (~dp[u][bit]) return dp[u][bit];
    if (!bit) return dist[u][n + 1];
    int tmp = INF;
    for (int v = 1; v <= n; v++)
        if (bit & (1 << v))
            tmp = min(tmp, dist[u][v] + 5 + dfs2(v, bit ^ (1 << v))); 
    return dp[u][bit] = tmp;
}

void dfs1(int idx) {
    if (idx == n + 1) {
        int tmp = 0;
        for (int i = 1; i <= group; i++)
            tmp = max(tmp, dfs2(0, mask[i]));
        cost = min(cost, tmp);
        return;
    }
    for (int i = 1; i <= group; i++)
        if (cnt[i] < 5) {
            cnt[i]++;
            mask[i] |= (1 << idx);
            dfs1(idx + 1);
            cnt[i]--;
            mask[i] ^= (1 << idx);
        }    
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        memset(dist, INF, sizeof dist);
        for (int i = 0; i <= n + 1; i++) dist[i][i] = 0;
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            dist[u][v] = dist[v][u] = min(dist[u][v], w);
        }
        for (int k = 0; k <= n + 1; k++)
            for (int i = 0; i <= n + 1; i++)
                for (int j = 0; j <= n + 1; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        cost = INF;
        memset(dp, 0xff, sizeof dp);
        group = n / 5 + (n % 5 ? 1 : 0);
        for (int i = 1; i <= group; i++) cnt[i] = mask[i] = 0;
        dfs1(1);
        cout << cost << '\n';
    }
    return 0;
}
