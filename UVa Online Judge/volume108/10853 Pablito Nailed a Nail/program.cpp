// Pablito Nailed a Nail
// UVa ID: 10853
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long L, aMin, aMax, bMin, bMax;

char solveGame() {
    if (L <= aMax) return 'A';
    long long d = aMax - aMin + bMin - bMax;
    long long q = (L - 1) / (aMin + bMax);
    if (d < 0 && q > ((bMax - bMin - aMax + d + 1) / d)) return 'B';
    return (((L - 1) % (aMin + bMax)) < (aMax + q * d)) ? 'A' : 'B';
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld %lld %lld %lld %lld", &L, &aMin, &aMax, &bMin, &bMax);
        printf("%c\n", solveGame());
    }
    return 0;
}
