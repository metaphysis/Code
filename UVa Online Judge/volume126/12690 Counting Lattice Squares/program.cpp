// Counting Lattice Squares
// UVa ID: 12690
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 输出 __int128
void printInt128(__int128 x) {
    if (x == 0) { putchar('0'); return; }
    if (x < 0) { putchar('-'); x = -x; }
    char s[50]; int p = 0;
    while (x > 0) { s[p++] = '0' + x % 10; x /= 10; }
    while (p--) putchar(s[p]);
}

int main() {
    int m, n;
    while (scanf("%d %d", &m, &n) == 2 && (m || n)) {
        int L = min(m, n);
        int t = (L + 1) / 2;                     // 奇数个数
        __int128 sum1 = (__int128)t * t;         // Σk
        __int128 sum2 = (__int128)t * (4LL * t * t - 1) / 3; // Σk²
        __int128 sum3 = (__int128)t * t * (2LL * t * t - 1); // Σk³
        __int128 term1 = (__int128)(m + 1) * (n + 1) * sum1;
        __int128 term2 = (__int128)(m + n + 2) * sum2;
        __int128 ans = term1 - term2 + sum3;
        printInt128(ans);
        putchar('\n');
    }
    return 0;
}
