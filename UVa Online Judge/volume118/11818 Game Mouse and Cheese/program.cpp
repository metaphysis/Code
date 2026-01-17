// Game Mouse and Cheese
// UVa ID: 11818
// Verdict: Accepted
// Submission Date: 2026-01-08
// UVa Run Time: 0.210s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

// Game Mouse and Cheese
// UVa ID: 11818
// Verdict: Accepted
// Submission Date: 2026-01-08
// UVa Run Time: 0.210s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 12条边的定义，每条边连接两个格子编号
const pair<int, int> edges[12] = {
    {1, 2}, {2, 3}, {4, 5}, {5, 6}, {7, 8}, {8, 9},
    {1, 4}, {2, 5}, {3, 6}, {4, 7}, {5, 8}, {6, 9}
};

// 坐标到边编号的映射，便于输入处理
map<pair<int, int>, int> magic = {
    {{10, 11}, 0}, {{20, 21}, 1}, {{11, 12}, 2},
    {{21, 22}, 3}, {{12, 13}, 4}, {{22, 23}, 5},
    {{1, 11}, 6}, {{11, 21}, 7}, {{21, 31}, 8},
    {{2, 12}, 9}, {{12, 22}, 10}, {{22, 32}, 11}
};

int S, C, R;  // 老鼠位置、奶酪位置、初始移除边数
int dp[1 << 12];  // 记忆化数组，-1表示未计算，1表示必胜，0表示必败

// 检查在边集合mask下，S和C是否连通
// mask中位为1表示边存在，为0表示边已被移除
bool isConnected(int edgeMask) {
    vector<vector<int>> g(10);  // 邻接表，1-indexed
    for (int i = 0; i < 12; i++) {
        if (!((edgeMask >> i) & 1)) {  // 边存在（未被移除）
            int u = edges[i].first, v = edges[i].second;
            g[u].push_back(v); 
            g[v].push_back(u);
        }
    }
    // BFS检查连通性
    vector<bool> visited(10, false);
    queue<int> q;
    q.push(S);
    visited[S] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (!visited[v]) {
                if (v == C) return true;  // 找到奶酪
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return false;  // 不连通
}

// 记忆化搜索，判断当前状态（剩余边集合edgeMask）下，当前玩家是否必胜
bool dfs(int edgeMask) {
    if (~dp[edgeMask]) return dp[edgeMask];  // 已计算过
    // 尝试所有可移除的边
    for (int i = 0; i < 12; i++) {
        if ((edgeMask >> i) & 1) {  // 第i条边存在
            int newMask = edgeMask ^ (1 << i);  // 移除该边
            if (isConnected(newMask)) return dp[edgeMask] = 1;  // 移除后连通，获胜
            if (!dfs(newMask)) return dp[edgeMask] = 1;  // 对手必败，我方必胜
        }
    }
    return dp[edgeMask] = 0;  // 所有走法都导致对手必胜，我方必败
}

int main() {
    int T; cin >> T;
    for (int caseNo = 1; caseNo <= T; caseNo++) {
        cin >> S >> C >> R;
        // 初始所有边都存在（12位全1）
        int initialMask = (1 << 12) - 1;
        // 移除初始给定的R条边
        for (int i = 0; i < R; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int t1 = x1 * 10 + y1, t2 = x2 * 10 + y2;
            if (t1 > t2) swap(t1, t2);
            initialMask &= ~(1 << magic[{t1, t2}]);
        }
        cout << "Case " << caseNo << ": ";
        // 检查初始状态是否已连通
        if (isConnected(initialMask)) {
            cout << "No Cheese!\n";
            continue;
        }
        // 记忆化搜索求解博弈
        memset(dp, -1, sizeof dp);
        bool sohaWins = dfs(initialMask);
        cout << (sohaWins ? "SOHA" : "TARA") << '\n';
    }
    return 0;
}
