// Protecting Zonk
// UVa ID: 12093
// Verdict: Accepted
// Submission Date: 2025-12-05
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net
//
// https://blog.csdn.net/metaphysis/article/details/155610601
//

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 10005;

vector<int> graph[MAXN];
int costSoldier, costSergeant;
int dp[MAXN][4];

void dfs(int u, int parent) {
    // 初始化
    dp[u][0] = 0;
    dp[u][1] = 0;
    dp[u][2] = costSergeant;
    dp[u][3] = 0;
    int minDiff = INF;
    for (int v : graph[u]) {
        if (v == parent) continue;
        dfs(v, u);
        // 状态0：需要子节点是状态1或2
        dp[u][0] += min(dp[v][1], dp[v][2]);
        // 计算tmp = min(dp(v,0), dp(v,1), dp(v,2))
        int tmp = min(dp[v][0], min(dp[v][1], dp[v][2]));
        // 状态1
        dp[u][1] += tmp;
        // 更新minDiff
        minDiff = min(minDiff, dp[v][2] - tmp);
        // 状态2
        dp[u][2] += min(tmp, dp[v][3]);
        // 状态3
        dp[u][3] += tmp;
    }
    // 状态1加上min(c1, minDiff)
    dp[u][1] += min(minDiff, costSoldier);
    // 处理叶子节点特殊情况
    if (graph[u].size() == 1 && parent != -1) dp[u][3] = INF;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n >> costSoldier >> costSergeant) {
        if (n == 0 && costSoldier == 0 && costSergeant == 0) break;
        for (int i = 1; i <= n; ++i) graph[i].clear();
        for (int i = 0; i < n - 1; ++i) {
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        dfs(1, -1);
        cout << min(dp[1][0], min(dp[1][1], dp[1][2])) << endl;
    }
    return 0;
}

