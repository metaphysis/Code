// Starting School
// UVa ID: 12598
// Verdict: Accepted
// Submission Date: 2026-01-16
// UVa Run Time: 0.280s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;
typedef long long ll;
ll assigned[MAXN], sorted[MAXN];

int main() {
    int T;
    scanf("%d", &T);
    for (int cs = 1; cs <= T; ++cs) {
        ll n, k, q;
        scanf("%lld %lld %lld", &n, &k, &q);
        for (int i = 0; i < k; ++i) scanf("%lld", &assigned[i]);
        memcpy(sorted, assigned, k * sizeof(long long));
        sort(sorted, sorted + k);
        printf("Case %d:\n", cs);
        while (q--) {
            ll p;
            scanf("%lld", &p);
            if (p <= k) printf("%lld\n", assigned[p - 1]);
            else {
                ll needed = p - k;
                ll left = 1, right = 2e9, answer = -1;
                while (left <= right) {
                    ll middle = (left + right) / 2;
                    ll cnt = upper_bound(sorted, sorted + k, middle) - sorted;
                    ll available = middle - cnt;
                    if (available >= needed) {
                        answer = middle;
                        right = middle - 1;
                    } else left = middle + 1;
                }
                printf("%lld\n", answer);
            }
        }
    }
    return 0;
}
