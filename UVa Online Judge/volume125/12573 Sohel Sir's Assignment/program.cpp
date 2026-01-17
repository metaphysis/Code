// Sohel Sir's Assignment
// UVa ID: 12573
// Verdict: Accepted
// Submission Date: 2026-01-15
// UVa Run Time: 0.220s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long x, y;
        cin >> x >> y;
        long long remainder = y - 2;
        if (remainder > x) {
            cout << "Impossible\n";
            continue;
        }
        if (remainder == 0) {
            cout << "1\n";
            continue;
        }
        if (remainder == x) {
            cout << x + 1 << '\n';
            continue;
        }
        long long d = x - remainder, m = (1LL << 60);
        for (long long i = 1; i * i <= d; i++)
            if (d % i == 0) {
                if (i > remainder) m = min(m, i);
                if ((d / i) > remainder) m = min(m, d / i);
            }
        if (m == (1LL << 60)) cout << "Impossible";
        else cout << m;
        cout << '\n';
    }
    return 0;
}
