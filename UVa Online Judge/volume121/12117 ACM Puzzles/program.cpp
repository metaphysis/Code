// ACM Puzzles
// UVa ID: 12117
// Verdict: Accepted
// Submission Date: 2026-01-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1000000000000LL;

// 22种拼图块的定义
char puzzleBlocks[22][3][4] = {
    {"*  ", "*  ", "*  "}, {"*  ", "** ", "*  "}, {"** ", " * ", "** "},
    {" * ", "** ", "** "}, {" * ", "***", " * "}, {"** ", "*  ", "** "},
    {" * ", "** ", " * "}, {"  *", " **", "** "}, {"** ", " **", "  *"},
    {" * ", "** ", "*  "}, {"*  ", "** ", " * "}, {"** ", "** ", "*  "},
    {"** ", "** ", " * "}, {"** ", "*  ", "*  "}, {"** ", " * ", " * "},
    {" **", "** ", "*  "}, {"*  ", "** ", " **"}, {"*  ", "*  ", "** "},
    {" * ", " * ", "** "}, {"***", " * ", " * "}, {" * ", " * ", "***"},
    {"*  ", "** ", "** "}
};

ll dp[2005][3][3][3];  // dp[i][p][q][r]

void initialize() {
    // 初始化dp数组为0
    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0] = 1;  // 起始状态

    for (int i = 0; i <= 2000; i++) {
        for (int p = 0; p < 3; p++)
        for (int q = 0; q < 3; q++)
        for (int r = 0; r < 3; r++) {
            ll currentVal = dp[i][p][q][r];
            if (currentVal == 0) continue;

            // 尝试放置22种块中的每一种
            for (int blockIdx = 0; blockIdx < 22; blockIdx++) {
                // 检查块左侧三列是否与当前偏移匹配
                if (puzzleBlocks[blockIdx][0][p] != '*' ||
                    puzzleBlocks[blockIdx][1][q] != '*' ||
                    puzzleBlocks[blockIdx][2][r] != '*') continue;

                // 检查左侧是否有额外填充（不能超出边界）
                if (p > 0 && puzzleBlocks[blockIdx][0][p-1] != ' ') continue;
                if (q > 0 && puzzleBlocks[blockIdx][1][q-1] != ' ') continue;
                if (r > 0 && puzzleBlocks[blockIdx][2][r-1] != ' ') continue;

                // 计算放置后的新偏移
                int newP = i + p, newQ = i + q, newR = i + r;
                for (int k = 0; k < 3; k++) {
                    if (puzzleBlocks[blockIdx][0][k] == '*') newP++;
                    if (puzzleBlocks[blockIdx][1][k] == '*') newQ++;
                    if (puzzleBlocks[blockIdx][2][k] == '*') newR++;
                }

                // 标准化偏移（减去最小值）
                int minVal = min({newP, newQ, newR});
                int offsetP = newP - minVal;
                int offsetQ = newQ - minVal;
                int offsetR = newR - minVal;

                // 更新dp值
                dp[minVal][offsetP][offsetQ][offsetR] += currentVal;
                if (dp[minVal][offsetP][offsetQ][offsetR] >= MOD)
                    dp[minVal][offsetP][offsetQ][offsetR] %= MOD;
            }
        }
    }
}

int main() {
    initialize();
    int n, caseNo = 1;
    while (cin >> n && n != 0)
        cout << "Case " << caseNo++ << ": " << dp[n][0][0][0] << "\n";
    return 0;
}
