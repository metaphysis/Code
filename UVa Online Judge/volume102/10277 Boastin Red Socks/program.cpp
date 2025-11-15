// Boastin Red Socks
// UVa ID: 10277
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    unsigned long p, q;
    while (cin >> p >> q) {
        if (p == 0 && q == 0) break;
        if (p == 0) {
            // 概率为0，最少袜子且能穿同色袜：0红2黑
            cout << "0 2" << endl;
            continue;
        }
        if (p == q) {
            // 概率为1，最少袜子：2红0黑
            cout << "2 0" << endl;
            continue;
        }
        unsigned long red = 0, black = 0;
        unsigned long minTotal = ULONG_MAX;
        for (unsigned long n = 2; n <= 50000; n++) {
            unsigned long long val = (unsigned long long)p * n * (n - 1);
            if (val % q != 0) continue;
            unsigned long long k = val / q;
            // 解 r*(r-1) = k
            unsigned long long d = 1 + 4 * k;
            unsigned long long sqrtD = sqrt(d);
            if (sqrtD * sqrtD != d) continue;
            if ((1 + sqrtD) % 2 != 0) continue;
            unsigned long r = (1 + sqrtD) / 2;
            if (r < 2 || r > n) continue;
            // 找到可行解
            if (n < minTotal) {
                minTotal = n;
                red = r;
                black = n - r;
            }
        }
        if (minTotal == ULONG_MAX) cout << "impossible" << '\n';
        else cout << red << " " << black << '\n';
    }
    return 0;
}
