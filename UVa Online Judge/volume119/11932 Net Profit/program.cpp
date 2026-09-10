#include <bits/stdc++.h>
using namespace std;

int n;                      // 节点数
vector<int> p;              // 利润
bool g[16][16];             // 邻接矩阵
int dp[1 << 16];            // 记忆化，dp[mask] 表示从该状态开始最终差值
int sumProfit;              // 总利润

// 深度优先搜索，返回从 mask 状态开始，当前玩家最优下的最终差值（先手总分 - 后手总分）
int solve(int mask) {
    if (mask == (1 << n) - 1) return 0;                 // 所有节点已选完
    int &res = dp[mask];
    if (res != INT_MIN) return res;
    bool isFirst = (__builtin_popcount(mask) % 2 == 0); // 当前轮到先手？
    int best = isFirst ? INT_MIN : INT_MAX;
    for (int v = 0; v < n; ++v) {
        if (mask & (1 << v)) continue;                  // v 已经选过
        if (mask != 0) {                                // 非初始状态，必须与已选集合相邻
            bool ok = false;
            for (int u = 0; u < n; ++u)
                if ((mask & (1 << u)) && g[u][v]) { ok = true; break; }
            if (!ok) continue;
        }
        int val = (isFirst ? p[v] : -p[v]) + solve(mask | (1 << v));
        if (isFirst) {
            if (val > best) best = val;
        } else {
            if (val < best) best = val;
        }
    }
    res = best;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n && n != 0) {
        p.resize(n);
        sumProfit = 0;
        for (int i = 0; i < n; ++i) { cin >> p[i]; sumProfit += p[i]; }
        // 初始化邻接矩阵
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                g[i][j] = false;
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            g[a][b] = g[b][a] = true;
        }
        // 重置 dp
        fill(dp, dp + (1 << n), INT_MIN);
        int diff = solve(0);                            // 最终差值
        int scoreFirst = (sumProfit + diff) / 2;
        int scoreSecond = (sumProfit - diff) / 2;
        if (scoreFirst > scoreSecond) {
            cout << "First player wins! " << scoreFirst << " to " << scoreSecond << ".\n";
        } else if (scoreFirst < scoreSecond) {
            cout << "Second player wins! " << scoreSecond << " to " << scoreFirst << ".\n";
        } else {
            cout << "Tie game! " << scoreFirst << " all.\n";
        }
    }
    return 0;
}
