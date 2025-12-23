// Regular Polygon
// UVa ID: 10824
// Verdict: Accepted
// Submission Date: 2025-12-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-8;
const double TWO_PI = 2.0 * PI;

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int caseNo = 1;
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        vector<double> angles;
        for (int i = 0; i < n; i++) {
            double x, y;
            scanf("%lf %lf", &x, &y);
            double ang = atan2(y, x);
            if (ang < 0) ang += TWO_PI;
            angles.push_back(ang);
        }
        sort(angles.begin(), angles.end());
        // 去重
        vector<double> uniqueAngles;
        for (double ang : angles)
            if (uniqueAngles.empty() || fabs(ang - uniqueAngles.back()) > EPS)
                uniqueAngles.push_back(ang);
        int m = uniqueAngles.size();
        vector<double> extended = uniqueAngles;
        for (int i = 0; i < m; i++) extended.push_back(uniqueAngles[i] + TWO_PI);
        vector<pair<int, int>> results;
        for (int k = 3; k <= m; k++) {
            double step = TWO_PI / k;
            int cnt = 0;
            // 扇形区域：[base, base + step)
            double base = uniqueAngles[0];
            double limit = base + step;  // 右边界（不包含）
            // 遍历所有点，但只检查扇形区域内的
            for (int i = 0; i < m; i++) {
                double angle = uniqueAngles[i];
                // 严格检查是否在扇形区域内
                // 注意：对于浮点数，我们需要容差处理
                if (angle >= base - EPS && angle < limit - EPS) {
                    double cur = angle;
                    bool valid = true;
                    for (int j = 1; j < k; j++) {
                        cur += step;
                        auto it = lower_bound(extended.begin(), extended.end(), cur - EPS);
                        if (it == extended.end() || fabs(*it - cur) > EPS) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) cnt++;
                }
            }
            if (cnt > 0) results.push_back({k, cnt});
        }
        printf("Case %d:\n", caseNo++);
        for (auto &p : results) printf("%d %d\n", p.first, p.second);
    }
    return 0;
}
