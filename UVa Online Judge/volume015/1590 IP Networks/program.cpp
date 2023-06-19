// IP Networks
// UVa ID: 1590
// Verdict: Accepted
// Submission Date: 2023-06-18
// UVa Run Time: 0.010s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
#define BIT(X, Y) ((X & (255LL << Y)) >> Y)
#define BINARY(X) BIT(X, 24), BIT(X, 16), BIT(X, 8), BIT(X, 0)
int main(int argc, char *argv[])
{
    int m;
    unsigned int a, b, c, d, minb, maxb, address, orb;
    while (scanf("%d", &m) == 1) {
        minb = -1, maxb = 0, address = -1;
        for (int i = 0; i < m; i++) {
            scanf("%d.%d.%d.%d", &a, &b, &c, &d);
            orb = (a << 24) | (b << 16) | (c << 8) | d;
            address &= orb, minb = min(minb, orb), maxb = max(maxb, orb);
        }
        unsigned int mask = -1;
        while (true) {
            if (minb >= address & (address | ~mask) >= maxb) {
                printf("%d.%d.%d.%d\n", BINARY(address));
                printf("%d.%d.%d.%d\n", BINARY(mask));
                break;
            }
            mask -= mask & -mask;
            address &= mask;
        }
    }
    return 0;
}
