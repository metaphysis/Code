// Pit Stop Strategy
// UVa ID: 10379
// Verdict: Accepted
// Submission Date: 2026-06-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;

int main() {
    int L;
    double t0, a, c0, b, p0, p1;
    while (cin >> L >> t0 >> a >> c0 >> b >> p0 >> p1) {
        printf("%d %.3f %.3f %.3f %.3f %.3f %.3f\n", L, t0, a, c0, b, p0, p1);
        
        // 预处理每段长度对应的油量和时间
        vector<double> fuel(L + 1), cost(L + 1);
        for (int len = 1; len <= L; ++len) {
            double low = 0, high = c0 * len * 100;
            for (int it = 0; it < 80; ++it) {
                double mid = (low + high) / 2, f = mid;
                for (int lap = 0; lap < len; ++lap) f -= c0 + b * f;
                (f > EPS ? high : low) = mid;
            }
            fuel[len] = (low + high) / 2;
            double f = fuel[len], t = 0;
            for (int lap = 0; lap < len; ++lap) t += t0 + a * f, f -= c0 + b * f;
            cost[len] = t;
        }
        
        // DP
        vector<double> dp(L + 1, 1e20);
        vector<int> pre(L + 1, -1);
        dp[0] = 0;
        for (int i = 1; i <= L; ++i) for (int len = 1; len <= i; ++len) {
            double pit = (i > len) ? (p0 + p1 * fuel[len]) : 0;
            double cand = dp[i - len] + cost[len] + pit;
            if (cand < dp[i] - EPS) dp[i] = cand, pre[i] = len;
        }
        
        // 回溯段长
        vector<int> segs;
        for (int i = L; i > 0; i -= pre[i]) segs.push_back(pre[i]);
        reverse(segs.begin(), segs.end());
        
        // 生成进站信息
        vector<pair<int, double>> stops;
        for (int i = 0, sum = 0; i < (int)segs.size(); ++i) {
            if (i > 0) stops.push_back({sum, fuel[segs[i]]});
            sum += segs[i];
        }
        
        // 输出
        printf("%.3f %.3f %d\n", dp[L], fuel[segs[0]], (int)stops.size());
        for (auto &s : stops) printf("%d %.3f\n", s.first, s.second);
    }
    return 0;
}
