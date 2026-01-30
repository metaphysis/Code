// Colorful Board
// UVa ID: 11725
// Verdict: Accepted
// Submission Date: 2026-01-30
// UVa Run Time: 0.370s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXR = 7;
const int MAXC = 7;

int M, N, R, C;
bool forbidden[MAXR][MAXC];
vector<int> validStates[MAXR];
vector<int> compat[MAXR][1 << 14]; // 兼容状态列表
int dp[MAXR][1 << 14]; // 状态数最多 4^7 = 16384
int stateMap[MAXR][1 << 21]; // 从编码到索引的映射

// 使用4种颜色编码：每列2位，0-3表示颜色
// 禁止格子用特殊值4表示，但实际不存储在状态中

void dfs(int row, int col, int mask, vector<int>& states) {
    if (col == C) {
        states.push_back(mask);
        return;
    }
    
    if (forbidden[row][col]) {
        // 禁止格子：标记为特殊值4（不在mask中，通过额外检查）
        dfs(row, col + 1, mask, states);
        return;
    }
    
    // 尝试4种颜色
    for (int color = 1; color <= 4; ++color) {
        // 检查左侧颜色是否相同
        if (col > 0 && !forbidden[row][col - 1]) {
            int leftColor = (mask >> (2 * (col - 1))) & 3;
            if (leftColor == color - 1) continue; // 颜色编号0-3
        }
        int newMask = mask | ((color - 1) << (2 * col));
        dfs(row, col + 1, newMask, states);
    }
}

// 检查两个状态是否兼容（考虑禁止格子）
bool checkCompat(int row1, int mask1, int row2, int mask2) {
    for (int col = 0; col < C; ++col) {
        if (forbidden[row1][col] || forbidden[row2][col]) continue;
        int c1 = (mask1 >> (2 * col)) & 3;
        int c2 = (mask2 >> (2 * col)) & 3;
        if (c1 == c2) return false;
    }
    return true;
}

void solve(int caseNo) {
    cin >> M >> N;
    R = M + 1;
    C = N + 1;
    memset(forbidden, 0, sizeof(forbidden));
    int K; cin >> K;
    for (int i = 0; i < K; ++i) {
        int x, y; cin >> x >> y;
        --x; --y;
        forbidden[x][y] = true;
    }
    // 生成所有有效状态
    for (int r = 0; r < R; ++r) {
        validStates[r].clear();
        dfs(r, 0, 0, validStates[r]);
    }
    // 为每行状态建立索引映射
    for (int r = 0; r < R; ++r)
        for (int i = 0; i < (int)validStates[r].size(); ++i)
            stateMap[r][validStates[r][i]] = i;
    // 预处理兼容性（只存下一行状态的索引）
    for (int r = 0; r < R - 1; ++r) {
        int size1 = validStates[r].size();
        int size2 = validStates[r + 1].size();
        for (int i = 0; i < size1; ++i) {
            compat[r][i].clear();
            for (int j = 0; j < size2; ++j)
                if (checkCompat(r, validStates[r][i], r + 1, validStates[r + 1][j]))
                    compat[r][i].push_back(j);
        }
    }
    // 动态规划
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < (int)validStates[0].size(); ++i) dp[0][i] = 1;
    for (int r = 0; r < R - 1; ++r) {
        int nextSize = validStates[r + 1].size();
        vector<int> nextDP(nextSize, 0);
        for (int i = 0; i < (int)validStates[r].size(); ++i) {
            if (dp[r][i] == 0) continue;
            int curVal = dp[r][i];
            for (int j : compat[r][i]) nextDP[j] = (nextDP[j] + curVal) % MOD;
        }
        for (int j = 0; j < nextSize; ++j) dp[r + 1][j] = nextDP[j];
    }
    // 计算结果
    long long result = 0;
    for (int i = 0; i < (int)validStates[R - 1].size(); ++i) 
        result = (result + dp[R - 1][i]) % MOD;
    cout << "Case " << caseNo << ": " << result << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) solve(t);
    return 0;
}
