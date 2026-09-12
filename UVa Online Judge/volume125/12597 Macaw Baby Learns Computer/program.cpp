// Macaw Baby Learns Computer
// UVa ID: 12597
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

long long solve(long long m, long long e) {
    long long maxExp = (1LL << e) - 1;
    if (maxExp <= m + 1) return (1LL << maxExp) - 1;
    return (1LL << (m + 1)) - 1 + (maxExp - m - 1) * (1LL << m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long m, e;
    while (cin >> m >> e) {
        if (m == 0 && e == 0) break;
        cout << solve(m, e) << '\n';
    }
    return 0;
}
