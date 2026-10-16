// Pipe Stream
// UVa ID: 1715
// Verdict: Wrong Answer
// Submission Date: 2026-10-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int solve() {
    long long l, v1, v2, t, s;
    cin >> l >> v1 >> v2 >> t >> s;
    assert(v1 < v2);
    assert(1 <= l && l <= 1000000000);
    assert(1 <= v1 && v1 <= 1000000000);
    assert(1 <= v2 && v2 <= 1000000000);
    assert(1 <= t && t <= 1000000000);
    assert(1 <= s && s <= 1000000000);
    __int128 v = v2, n = 1;
    for (int k = 0; ; k++) {
        if (__int128(t) * n >= v - v1)
            return k;
        if (n <= 0)
            return -1;
        __int128 d = __int128(k + 1) * s;
        if (v * d > l + __int128(t) * d) {
            __int128 numerator = (v - t) * d - l, denominator = __int128(t) * d;
            __int128 nf = (numerator + denominator - 1) / denominator;
            v -= nf * t;
            n = 2 * (n - nf);
        } else {
            n *= 2;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c;
    cin >> c;
    assert(1 <= c && c <= 100);
    while (c--) {
        int answer = solve();
        if (answer == -1)
            cout << "impossible\n";
        else
            cout << answer << '\n';
    }
    return 0;
}
