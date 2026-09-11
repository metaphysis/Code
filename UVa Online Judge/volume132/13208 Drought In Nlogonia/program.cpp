// Drought In Nlogonia
// UVa ID: 13208
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.270s

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long a;
        int n;
        scanf("%lld %d", &a, &n);
        vector<long long> x(n + 1); // 1-indexed, x[1..n]
        for (int i = 1; i <= n; ++i) scanf("%lld", &x[i]);
        vector<long long> h(n + 1); // h[0..n]
        for (int i = 0; i <= n; ++i) scanf("%lld", &h[i]);

        // 计算每个隔间左侧最大墙高和右侧最大墙高
        vector<long long> leftMax(n + 2), rightMax(n + 2);
        leftMax[0] = h[0];
        for (int i = 1; i <= n; ++i) leftMax[i] = max(leftMax[i - 1], h[i]);
        rightMax[n] = h[n];
        for (int i = n - 1; i >= 0; --i) rightMax[i] = max(rightMax[i + 1], h[i]);

        long long area = 0; // 横截面积，单位平方米
        for (int i = 1; i <= n; ++i) {
            long long waterHeight = min(leftMax[i - 1], rightMax[i]);
            area += waterHeight * x[i];
        }

        long long ans = area * a; // 体积 = 横截面积 * 深度
        printf("%lld\n", ans);
    }
    return 0;
}
