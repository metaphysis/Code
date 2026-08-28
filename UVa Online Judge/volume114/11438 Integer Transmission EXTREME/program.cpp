#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

int solve() {
    int n, d, cas = 0;
    cpp_int key;
    while (cin >> n) {
        if (n == 0)
            break;
        cin >> d >> key;
        string str;
        str.reserve(n);
        for (int i = 0; i < n; i++)
            str += (((key >> (n - i - 1)) & 1) != 0) + '0';
        vector<int> pre(n + 1, 0), low(n + 1, n), high(n + 1, -1);
        for (int i = 1; i <= n; i++)
            pre[i] = pre[i - 1] + (str[i - 1] == '1');
        for (int t = 1; t <= n; t++) {
            for (int m = 1; m <= n + 1; m++) {
                int len = 0;
                if (m <= n)
                    len = min(n, m + d) - m + 1;
                int r = t - m + 1;
                if (r < 0 || r > len)
                    continue;
                int one = pre[min(n, m + d)] - pre[m - 1];
                int zero = len - one;
                int mn = pre[m - 1] + max(0, r - zero);
                int mx = pre[m - 1] + min(r, one);
                low[t] = min(low[t], mn);
                high[t] = max(high[t], mx);
            }
        }
        vector<vector<char> > can(n + 1, vector<char>(n + 1, 0));
        int tot = pre[n];
        can[n][tot] = 1;
        for (int t = n - 1; t >= 0; t--) {
            for (int j = 0; j <= n; j++) {
                if (t > 0 && (j < low[t] || j > high[t]))
                    continue;
                if (j <= n && can[t + 1][j])
                    can[t][j] = 1;
                if (j < n && can[t + 1][j + 1])
                    can[t][j] = 1;
            }
        }
        vector<cpp_int> dp(n + 1), nxt(n + 1);
        dp[0] = 1;
        for (int t = 0; t < n; t++) {
            fill(nxt.begin(), nxt.end(), 0);
            for (int j = 0; j <= t; j++) {
                if (dp[j] == 0)
                    continue;
                if (j >= low[t + 1] && j <= high[t + 1])
                    nxt[j] += dp[j];
                if (j + 1 >= low[t + 1] && j + 1 <= high[t + 1])
                    nxt[j + 1] += dp[j];
            }
            dp.swap(nxt);
        }
        cpp_int cnt = dp[tot], mn = 0, mx = 0;
        int one = 0;
        for (int t = 0; t < n; t++) {
            int bit = 0;
            if (can[t + 1][one] == 0)
                bit = 1;
            mn = mn * 2 + bit;
            one += bit;
        }
        one = 0;
        for (int t = 0; t < n; t++) {
            int bit = 1;
            if (one + 1 > n || can[t + 1][one + 1] == 0)
                bit = 0;
            mx = mx * 2 + bit;
            one += bit;
        }
        cout << "Case " << ++cas << ": " << cnt << ' ' << mn << ' ' << mx << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
