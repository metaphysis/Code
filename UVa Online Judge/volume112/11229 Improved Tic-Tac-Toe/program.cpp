// Improved Tic-Tac-Toe
// UVa ID: 11229
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.520s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_STATE = 19683;   // 3^9

int pow3[9];
double prob1[9], prob2[9];
double memo[MAX_STATE][2];
bool visited[MAX_STATE][2];

// 获取 state 中位置 pos 的符号 (0空,1先手,2后手)
inline int getSym(int state, int pos) {
    return (state / pow3[pos]) % 3;
}

// 在 state 的 pos 位置放置符号 sym (1或2)，要求原位置为空
inline int setSym(int state, int pos, int sym) {
    return state + sym * pow3[pos];
}

// 检查棋盘是否已满
inline bool isFull(int state) {
    for (int i = 0; i < 9; ++i)
        if (getSym(state, i) == 0) return false;
    return true;
}

// 检查胜利者，返回 0 无胜者，1 先手胜，2 后手胜
int checkWin(int state) {
    const int lines[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},  // 行
        {0,3,6}, {1,4,7}, {2,5,8},  // 列
        {0,4,8}, {2,4,6}            // 对角线
    };
    for (int i = 0; i < 8; ++i) {
        int a = getSym(state, lines[i][0]);
        int b = getSym(state, lines[i][1]);
        int c = getSym(state, lines[i][2]);
        if (a != 0 && a == b && b == c) return a;
    }
    return 0;
}

// dfs 返回当前状态下先手胜率 (0~1)
double dfs(int state, int turn) {
    int win = checkWin(state);
    if (win != 0) return (win == 1 ? 1.0 : 0.0);
    if (isFull(state)) return 0.0;

    if (visited[state][turn]) return memo[state][turn];
    visited[state][turn] = true;

    int playerSym = turn + 1;       // 1 或 2
    int otherSym = 3 - playerSym;
    double best = (turn == 0 ? 0.0 : 1.0);   // 先手最大化，后手最小化

    for (int pos = 0; pos < 9; ++pos) {
        if (getSym(state, pos) != 0) continue;

        // 答对分支：放置当前玩家符号
        int nsCorrect = setSym(state, pos, playerSym);
        int winC = checkWin(nsCorrect);
        double valC;
        if (winC != 0) valC = (winC == 1 ? 1.0 : 0.0);
        else valC = dfs(nsCorrect, 1 - turn);

        // 答错分支：放置对手符号
        int nsWrong = setSym(state, pos, otherSym);
        int winW = checkWin(nsWrong);
        double valW;
        if (winW != 0) valW = (winW == 1 ? 1.0 : 0.0);
        else valW = dfs(nsWrong, 1 - turn);

        double prob = (turn == 0 ? prob1[pos] : prob2[pos]);   // 答对概率
        double expected = prob * valC + (1.0 - prob) * valW;

        if (turn == 0) {
            if (expected > best) best = expected;
        } else {
            if (expected < best) best = expected;
        }
    }

    memo[state][turn] = best;
    return best;
}

int main() {
    // 预计算 3 的幂
    pow3[0] = 1;
    for (int i = 1; i < 9; ++i) pow3[i] = pow3[i-1] * 3;

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        // 读取先手概率网格（9个整数）
        for (int i = 0; i < 9; ++i) { cin >> prob1[i]; prob1[i] /= 100.0; }
        // 读取后手概率网格
        for (int i = 0; i < 9; ++i) { cin >> prob2[i]; prob2[i] /= 100.0; }

        // 清空记忆化标记
        for (int s = 0; s < MAX_STATE; ++s)
            for (int t = 0; t < 2; ++t)
                visited[s][t] = false;

        double ans = dfs(0, 0) * 100.0;   // 转换成百分比
        cout << "Case #" << tc << ": " << fixed << setprecision(2) << ans << "\n";
    }
    return 0;
}
