// Up the Ante
// UVa ID: 10811
// Verdict: Accepted
// Submission Date: 2026-03-01
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double P0 = 5.0 / 7.0;  // 20/28
const double P1 = 1.0 / 7.0;  // 4/28
const double P2 = 1.0 / 14.0; // 2/28
const double P3 = 1.0 / 14.0; // 2/28

int k, m, l;
map<tuple<int, int, int>, double> dp;

double dfs(int net, int round, int stage) {
    if (round > k && net > 0) return 1.0;
    if (round > m) return 0.0;
    auto key = make_tuple(net, round, stage);
    if (dp.count(key)) return dp[key];
     // 检查赌注是否超限，如果超限则重置stage
    int currentStage = stage;
    if ((1 << currentStage) > l) currentStage = 0;
    int bet = 1 << currentStage;
    double r = 0.0;
    // 输：净收益减少bet，stage+1
    r += P0 * dfs(net - bet, round + 1, currentStage + 1);
    // 赢1次：净收益增加bet，stage重置为0
    r += P1 * dfs(net + bet, round + 1, 0);
    // 赢2次：净收益增加2*bet，stage重置为0
    r += P2 * dfs(net + 2 * bet, round + 1, 0);
    // 赢3次：净收益增加3*bet，stage重置为0
    r += P3 * dfs(net + 3 * bet, round + 1, 0);
    return dp[key] = r;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        scanf("%d %d %d", &k, &m, &l);
        dp.clear();
        printf("%.4f\n", dfs(0, 1, 0));
    }
    return 0;
}
