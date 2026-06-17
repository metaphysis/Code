// Exam
// UVa ID: 1655
// Verdict: Accepted
// Submission Date: 2026-06-17
// UVa Run Time: 1.120s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, limit;

ll work() {
    ll tmp, res = 0;
    res = limit;
    for (ll i = 1; i <= limit; ++i) {
        tmp = n / (i * i) - i;
        if (tmp > 0) res += 3 * tmp;
        for (ll j = i + 1; i * j * j <= n; ++j) {
            tmp = n / (i * j) - j;
            if (tmp > 0) res += 6 * tmp;
            res += 3;
        }
    }
    return res;
}

int main() {
    int caseNo = 0;
    while (scanf("%lld", &n) != EOF) {
        limit = pow((long double)n, 1.0L / 3.0L);
        while ((limit + 1) * (limit + 1) * (limit + 1) <= n) ++limit;
        while (limit * limit * limit > n) --limit;
        printf("Case %d: %lld\n", ++caseNo, work());
    }
    return 0;
}
