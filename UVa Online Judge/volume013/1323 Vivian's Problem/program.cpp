#include <bits/stdc++.h>
using namespace std;

int getMask(long long x, const vector<long long>& ms) {
    int mask = 0;
    for (int i = 0; i < 8; i++) {
        if (x % ms[i] == 0) {
            int cnt = 0;
            while (x % ms[i] == 0) {
                x /= ms[i];
                cnt++;
            }
            if (cnt > 1) return -1;
            mask |= 1 << i;
        }
    }
    if (x != 1) return -1;
    return mask;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<long long> ms = {3, 7, 31, 127, 8191, 131071, 524287, 2147483647LL};
    vector<int> val = {2, 3, 5, 7, 13, 17, 19, 31};
    int k;
    while (cin >> k) {
        vector<int> dp(256, -1);
        dp[0] = 0;
        for (int i = 0; i < k; i++) {
            long long x;
            cin >> x;
            int mask = getMask(x, ms);
            if (mask == -1) continue;
            for (int s = 255; s >= 0; s--) {
                if (dp[s] == -1 || (s & mask) != 0) continue;
                int add = 0;
                for (int j = 0; j < 8; j++)
                    if (mask & (1 << j)) add += val[j];
                dp[s | mask] = max(dp[s | mask], dp[s] + add);
            }
        }
        int ans = 0;
        for (int s = 1; s < 256; s++) ans = max(ans, dp[s]);
        if (ans == 0) cout << "NO\n";
        else cout << ans << '\n';
    }
    return 0;
}
