// Plants vs. Zombies HD SP
// UVa ID: 12452
// Verdict: Accepted
// Submission Date: 2026-05-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 10005;

vector<int> G[MAXN];
int dp[MAXN][2];
int cost[4] = {0, 100, 175, 500};

void dfs(int u, int parent) {
    dp[u][0] = dp[u][1] = INF;
    bool isLeaf = true;
    int sum1 = 0;      // 所有子节点取 dp[v][1] 的和
    int sum3 = 0;      // 所有子节点取 min(dp[v][0], dp[v][1]) 的和
    int maxDiff = 0, maxDiff2 = 0;  // 最大的两个差值 dp[v][1] - dp[v][0]
    
    for (int v : G[u]) if (v != parent) {
        isLeaf = false;
        dfs(v, u);
        sum1 += dp[v][1];
        sum3 += min(dp[v][0], dp[v][1]);
        int diff = dp[v][1] - dp[v][0];
        if (diff > maxDiff2) {
            maxDiff2 = diff;
            if (maxDiff2 > maxDiff) swap(maxDiff, maxDiff2);
        }
    }
    
    // 叶子节点
    if (isLeaf) {
        dp[u][0] = 0;
        dp[u][1] = cost[1];
        return;
    }
    
    // dp[u][0]: 不覆盖父边
    // 豌豆：覆盖1条子边
    dp[u][0] = sum1 - maxDiff + cost[1];
    // 分裂：覆盖2条子边
    if (maxDiff2 > 0)  // 需要两个不同的子节点
        dp[u][0] = min(dp[u][0], sum1 - maxDiff - maxDiff2 + cost[2]);
    // 不放植物：所有子边由子节点覆盖
    dp[u][0] = min(dp[u][0], sum1);
    
    // dp[u][1]: 覆盖父边
    // 豌豆：覆盖父边
    dp[u][1] = sum1 + cost[1];
    // 分裂：覆盖父边 + 1条子边
    dp[u][1] = min(dp[u][1], sum1 - maxDiff + cost[2]);
    // 杨桃：覆盖所有边
    dp[u][1] = min(dp[u][1], sum3 + cost[3]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) G[i].clear();
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(0, -1);
        cout << "$" << min(dp[0][0], dp[0][1]) << "\n";
    }
    return 0;
}
