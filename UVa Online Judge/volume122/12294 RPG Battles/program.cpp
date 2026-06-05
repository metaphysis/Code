// RPG Battles
// UVa ID: 12294
// Verdict: Accepted
// Submission Date: 2026-06-05
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double INF = 1e20;
const int MAX_POWER = 100;
const int MAX_DOUBLE = 7;

struct Battle {
    int p1, p2, t1, t2, w1, w2;
};

double battleTime(int power, const Battle& b) {
    if (power < b.p1) return INF;
    if (power > b.p2) return b.t2;
    return b.t1 - (b.t1 - b.t2) * (power - b.p1) / (double)(b.p2 - b.p1);
}

int main() {
    int n, p;
    while (cin >> n >> p && (n || p)) {
        vector<Battle> battles(n);
        for (int i = 0; i < n; ++i) 
            cin >> battles[i].p1 >> battles[i].p2 >> battles[i].t1 >> battles[i].t2 >> battles[i].w1 >> battles[i].w2;

        // dp[战斗场次][力量][双倍药水数] = 最小时间
        vector<vector<vector<double>>> dp(n + 1, vector<vector<double>>(MAX_POWER + 1, vector<double>(MAX_DOUBLE + 1, INF)));
        dp[0][min(p, MAX_POWER)][0] = 0.0;

        for (int i = 0; i < n; ++i) {
            const Battle& b = battles[i];
            for (int powerPrev = 1; powerPrev <= MAX_POWER; ++powerPrev) {
                for (int dPrev = 0; dPrev <= MAX_DOUBLE; ++dPrev) {
                    if (dp[i][powerPrev][dPrev] >= INF) continue;

                    // 尝试使用 bUsed 瓶双倍药水（0 ≤ bUsed ≤ dPrev）
                    for (int bUsed = 0; bUsed <= dPrev; ++bUsed) {
                        // 计算使用 bUsed 瓶双倍药水后的力量
                        int powerBefore = powerPrev;
                        for (int k = 0; k < bUsed; ++k) {
                            powerBefore *= 2;
                            if (powerBefore > MAX_POWER) {
                                powerBefore = MAX_POWER;
                                break;
                            }
                        }

                        double timeCost = battleTime(powerBefore, b);
                        if (timeCost >= INF) continue;

                        // 战斗后立即用掉所有力量药水（加法无损失）
                        int powerAfter = powerBefore + b.w1;
                        if (powerAfter > MAX_POWER) powerAfter = MAX_POWER;

                        // 剩余双倍药水 = 之前剩余的(dPrev - bUsed) + 新获得的b.w2
                        int dAfter = dPrev - bUsed + b.w2;
                        if (dAfter > MAX_DOUBLE) dAfter = MAX_DOUBLE;

                        dp[i + 1][powerAfter][dAfter] = min(dp[i + 1][powerAfter][dAfter], dp[i][powerPrev][dPrev] + timeCost);
                    }
                }
            }
        }

        double ans = INF;
        for (int power = 1; power <= MAX_POWER; ++power)
            for (int d = 0; d <= MAX_DOUBLE; ++d)
                ans = min(ans, dp[n][power][d]);

        if (ans >= INF) cout << "Impossible" << endl;
        else printf("%.2f\n", ans);
    }
    return 0;
}
