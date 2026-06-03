// Simple Equations Extreme
// UVa ID: 11571
// Verdict: Accepted
// Submission Date: 2026-06-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll A, B, C;

// 计算 f(t) = t^3 - A*t^2 + (A^2-C)/2 * t - B
long double f(long double t) {
    return t * t * t - A * t * t + (1.0l * A * A - C) * t * 0.5l - B;
}

// 在区间 [lo, hi] 内二分求根
// sig = 1 时找 f(t) < 0 的部分，sig = -1 时找 f(t) > 0 的部分
long double solve(long double lo, long double hi, int sig) {
    for (int i = 0; i < 200; ++i) {
        long double mid = (lo + hi) * 0.5l;
        if ((f(mid) < 0) == (sig > 0)) lo = mid;
        else hi = mid;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while (N--) {
        cin >> A >> B >> C;
        // 剪枝：3C 明显小于 A^2 时无实根
        if (3.0l * C < 0.9l * A * A) {
            cout << "No solution.\n";
            continue;
        }
        // 计算三个根所在的区间端点
        long double D = max((3.0l * C - 1.0l * A * A) * 0.5l, 0.0l);
        long double a = (A - sqrtl(D)) / 3.0l;
        long double b = (A + sqrtl(D)) / 3.0l;
        // 分别在三个区间内求根
        ll x1 = llround(solve(-1e20l, a, 1));
        ll x2 = llround(solve(a, b, -1));
        ll x3 = llround(solve(b, 1e20l, 1));
        // 验证整数解（必须严格递增，三个不同整数）
        if (x1 + x2 + x3 == A && x1 * x2 * x3 == B &&
            x1 * x1 + x2 * x2 + x3 * x3 == C &&
            x1 < x2 && x2 < x3)
            cout << x1 << " " << x2 << " " << x3 << "\n";
        else
            cout << "No solution.\n";
    }
    return 0;
}
