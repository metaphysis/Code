// Rocket Stages
// UVa ID: 11502
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Stage {
    long long S, L, T, C;
};

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int N;
        cin >> N;
        vector<Stage> stages(N);
        for (int i = 0; i < N; ++i)
            cin >> stages[i].S >> stages[i].L >> stages[i].T >> stages[i].C;

        const int MAXM = 10000;
        const double NEG_INF = -1e100;
        vector<double> dp(MAXM + 1, NEG_INF);
        dp[0] = 0.0;

        for (int i = 0; i < N; ++i) {
            long long S = stages[i].S, L = stages[i].L;
            long long T = stages[i].T, C = stages[i].C;
            long long self = S + L;
            if (self > MAXM || C == 0) continue;   // 无法选择或无效消耗率

            // 逆序更新，保证每个级只使用一次
            for (int m = MAXM - (int)self; m >= 0; --m) {
                if (dp[m] < NEG_INF / 2) continue;
                long long startMass = m + self;          // 开始燃烧时总质量
                long long endMass = m + S;               // 燃料烧完但结构未丢时的质量（分母）
                if (endMass <= 0) continue;              // 防止 log(0) 或负数

                // 安全条件：10*T >= 98*startMass （等价于 T >= 9.8*startMass）
                if (10LL * T < 98LL * startMass) continue;

                // 速度增量
                double delta = (double)T / C * log((double)startMass / (double)endMass)
                             - 9.8 * ((double)L / C);

                int newMass = m + (int)self;
                if (dp[m] + delta > dp[newMass])
                    dp[newMass] = dp[m] + delta;
            }
        }

        double best = NEG_INF;
        for (int m = 1; m <= MAXM; ++m)
            if (dp[m] > best) best = dp[m];

        // 四舍五入到最接近的整数
        int ans = (int)floor(best + 0.5);
        cout << ans << '\n';
    }
    return 0;
}
