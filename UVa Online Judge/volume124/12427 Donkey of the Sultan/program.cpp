// Donkey of the Sultan
// UVa ID: 12427
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

long long countEven(long long l, long long r) {
    if (l > r) return 0;
    return r / 2 - (l + 1) / 2 + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        long long a1, a2, b1, b2, c1, c2;
        cin >> a1 >> a2 >> b1 >> b2 >> c1 >> c2;
        long long ans = countEven(a1, a2) * (b2 - b1 + 1) * countEven(c1, c2);
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
