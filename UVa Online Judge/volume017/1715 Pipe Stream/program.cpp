// Pipe Stream
// UVa ID: 1715
// Verdict: Accepted
// Submission Date: 2026-10-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int solve() {
    long long l, v1, v2, t, s;
    cin >> l >> v1 >> v2 >> t >> s;
    __int128 v = v2, n = 1;
    for (int k = 0; ; ++k) {
        if (__int128(t) * n >= v - v1) return k;
        if (n <= 0) return -1;
        __int128 d = (__int128(k) + 1) * s;
        if (v * d > __int128(l) + __int128(t) * d) {
            __int128 numerator = (v - t) * d - l;
            __int128 denominator = __int128(t) * d;
            __int128 nf = (numerator + denominator - 1) / denominator;
            v -= nf * t;
            n = 2 * (n - nf);
        } else n *= 2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c;
    while (cin >> c) {
        while (c--) {
            int answer = solve();
            if (answer == -1) cout << "impossible\n";
            else cout << answer << '\n';
        }
    }
    return 0;
}
