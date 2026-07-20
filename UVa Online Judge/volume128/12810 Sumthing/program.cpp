// Sumthing
// UVa ID: 12810
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1000000009LL;
const ll INV2 = 500000005LL; // (MOD+1)/2

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        ll prod = 1;
        for (int i = 0; i < n; ++i) {
            ll a;
            cin >> a;
            ll term = (1 + 2 * a) % MOD; // 1 + 2*A_i
            prod = prod * term % MOD;
        }
        ll ans = (prod - 1 + MOD) % MOD;
        ans = ans * INV2 % MOD;
        cout << ans << '\n';
    }
    return 0;
}
