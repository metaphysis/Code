// Caravan Robbers
// UVa ID: 1616
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int f, b;
    bool operator<(const Interval& that) const {
        return b < that.b;
    }
};

Interval intervals[100005];

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) scanf("%d%d", &intervals[i].f, &intervals[i].b);
        sort(intervals, intervals + n);

        double left = 0, right = 1000000;
        while (right - left > 1e-9) {
            double mid = left + (right - left) / 2;
            double pos = 0;
            int i;
            for (i = 0; i < n; i++) {
                if (pos < intervals[i].f) pos = intervals[i].f;
                if (pos + mid > intervals[i].b) break;
                pos += mid;
            }
            if (i == n) left = mid;
            else right = mid;
        }

        int numerator = 0, denominator = 1;
        for (int d = 1; d <= n; d++) {
            int c = round(left * d);
            if (fabs(1.0 * numerator / denominator - left) > fabs(1.0 * c / d - left)) {
                numerator = c;
                denominator = d;
            }
        }
        printf("%d/%d\n", numerator, denominator);
    }
    return 0;
}
