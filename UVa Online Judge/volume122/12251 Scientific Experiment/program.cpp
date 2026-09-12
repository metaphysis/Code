#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n;
        long long x, y, z;
        cin >> n >> x >> y >> z;
        vector<long long> dp0(n + 1), dp1(n + 1);
        dp0[1] = 0;
        dp1[1] = -x / 2;
        for (int len = 2; len <= n; len++) {
            long long best = LLONG_MAX;
            for (int left = 1; left < len; left++) {
                long long cur = max(dp0[left], dp1[len - left]);
                best = min(best, cur);
            }
            dp0[len] = x + y + best;
            dp1[len] = z + best;
        }
        cout << "Case " << tc << ": " << dp0[n] << '\n';
    }
    return 0;
}
