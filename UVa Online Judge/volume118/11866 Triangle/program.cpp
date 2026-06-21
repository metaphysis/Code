// Triangle
// UVa ID: 11866
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long sumSq(int d1, int d2) {
    if (d1 > d2) return 0;
    auto f = [](int n) -> long long { return 1LL * n * (n + 1) * (2 * n + 1) / 6; };
    return f(d2) - f(d1 - 1);
}

long long countTriangles(int L, int R) {
    long long ans = 0;

    // 区间 A: c ∈ [L, min(R, 2L-3)]
    if (L >= 3) {
        int highA = min(R, 2 * L - 3);
        if (highA >= L) {
            int T = highA - L + 1;
            ans += 1LL * (T + 2) * (T + 1) * T / 6; // C(T+2,3)
        }
    }

    // 区间 B: c ∈ [max(L, 2L-2), min(R, 2L)]，最多三个值
    int lowB = max(L, 2 * L - 2);
    int highB = min(R, 2 * L);
    for (int c = lowB; c <= highB; ++c) {
        int B0 = c / 2 + 1;
        long long n = c - B0 + 1;
        ans += 1LL * (B0 + c) * n / 2 + (1LL - L) * n;
    }

    // 区间 C: c ∈ [max(L, 2L+1), R]
    int lowC = max(L, 2 * L + 1);
    int highC = R;
    if (lowC <= highC) {
        // 偶数 c = 2k
        int kStartEven = max((lowC + 1) / 2, L + 1);
        int kEndEven = highC / 2;
        if (kStartEven <= kEndEven) {
            int d1 = kStartEven - L, d2 = kEndEven - L;
            long long n = d2 - d1 + 1;
            long long sumD = 1LL * (d1 + d2) * n / 2;
            long long sumD2 = sumSq(d1, d2);
            ans += sumD2 + (2LL * L + 1) * sumD + 1LL * L * (L + 3) / 2 * n;
        }

        // 奇数 c = 2k+1
        int kStartOdd = max(lowC / 2, L);
        int kEndOdd = (highC - 1) / 2;
        if (kStartOdd <= kEndOdd) {
            int d1 = kStartOdd - L, d2 = kEndOdd - L;
            long long n = d2 - d1 + 1;
            long long sumD = 1LL * (d1 + d2) * n / 2;
            long long sumD2 = sumSq(d1, d2);
            ans += sumD2 + (2LL * L + 2) * sumD + (1LL * L * (L + 5) / 2 + 1) * n;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int X, Y;
        cin >> X >> Y;
        cout << countTriangles(X, Y) << '\n';
    }
    return 0;
}
